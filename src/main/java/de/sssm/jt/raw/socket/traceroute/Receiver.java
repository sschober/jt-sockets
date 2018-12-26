/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package de.sssm.jt.raw.socket.traceroute;

import de.sssm.jt.protocol.JtIcmpPacket;
import de.sssm.jt.protocol.JtIpPacket;
import de.sssm.jt.protocol.JtUdpPacket;
import de.sssm.jt.protocol.NoPacketException;
import de.sssm.jt.raw.socket.JtDatagramPacket;
import de.sssm.jt.raw.socket.JtIcmpSocket;
import de.sssm.jt.raw.socket.JtReceiveTimeoutException;
import java.util.SortedMap;
import java.util.TreeMap;
import java.util.concurrent.CountDownLatch;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author sven
 */
public class Receiver implements Runnable {

    private final JtIcmpSocket receiverSocket;
    private final String target;
    private final int basePort;
    private final CountDownLatch lock;
    private final SortedMap<Integer,String> hops = new TreeMap<>();

    public SortedMap<Integer, String> getHops() {
        return hops;
    }
    
    public Receiver(JtIcmpSocket receiverSocket, String target, final int basePort, CountDownLatch lock) {
        this.receiverSocket = receiverSocket;
        this.receiverSocket.open();
        this.receiverSocket.setTimeOut(2, 0);
        this.target = target;
        this.basePort = basePort;
        this.lock = lock;
    }
    
    @Override
    public void run() {
        boolean reached = false;
        int destHop = -1;
        while(!Thread.interrupted()){
            try {
                JtDatagramPacket result = receiverSocket.recvfrom();
                JtIpPacket ipPacket = JtIpPacket.fromBytes(result.bytes);
                JtIcmpPacket icmpPacket = JtIcmpPacket.fromBytes(ipPacket.getPayload());
                JtIpPacket innerIpPacket = JtIpPacket.fromBytes(icmpPacket.getPayload());
                JtUdpPacket innerUdpPacket = JtUdpPacket.fromBytes(innerIpPacket.getPayload());
                // System.err.println("source port: " + innerUdpPacket.getSourcePort() + " destination port: " + innerUdpPacket.getDestPort());
                int hop =  innerUdpPacket.getDestPort() - basePort;
                if(target.equals(result.sourceAddress)){
                    if(!reached){
                        destHop = hop;
                        reached = true;
                    }
                    else{
                        continue;
                    }
                }
                if(!hops.containsKey(hop)){
                    //System.out.println(String.format("[%2d] %s", hop, result.sourceAddress));
                    hops.put(hop, result.sourceAddress);
                }
                
                if(reached && allAccountedFor(hops)){
                    break;
                }
                
            } catch (NoPacketException ex) {
                System.err.println("no packet: " + ex.getMessage());
                break;
            } catch( JtReceiveTimeoutException jtrte){
                System.err.println("time out occured; could not reach destination");
                break;
            }
        }
        lock.countDown();
    }

    private boolean allAccountedFor(SortedMap<Integer, String> hops) {
        for(int i = Sender.STARTING_TTL; i < hops.size(); i++){
            if(!hops.containsKey(i)){
                System.err.println("still waiting for: " + i);
                return false; // we found a missing packet
            }
        }
        return true; // all there
    }
    
}

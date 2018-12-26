/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package de.sssm.jt.raw.socket.traceroute;

import de.sssm.jt.raw.socket.JtDatagramSocket;
import de.sssm.jt.raw.socket.JtIcmpSocket;
import java.util.SortedMap;
import java.util.concurrent.CountDownLatch;

/**
 *
 * @author sven
 */
public class TraceRoute {
    private final static CountDownLatch lock = new CountDownLatch(2);
    private final static int BASE_PORT = 55555;
    
    public static void main(String[] args) throws InterruptedException {
        if(args.length < 1){
            usage();
            die();
        }
        final String target = args[0];
        Sender sender = new Sender(new JtDatagramSocket(), target, BASE_PORT, lock);
        Thread senderThread = new Thread(sender);
        Receiver receiver = new Receiver(new JtIcmpSocket(), target, BASE_PORT, lock);
        new Thread(receiver).start();
        senderThread.start();
        lock.await();
        
        SortedMap<Integer, String> hops = receiver.getHops();
        for(SortedMap.Entry<Integer,String> entry : hops.entrySet()){
            System.out.println(String.format("[%2d] %s", entry.getKey(), entry.getValue()));
        }
    }

    private static void usage() {
        System.err.println("no target given");
    }

    private static void die() {
        System.exit(1);
    }

}

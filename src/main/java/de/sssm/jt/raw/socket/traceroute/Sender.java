/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package de.sssm.jt.raw.socket.traceroute;

import de.sssm.jt.raw.socket.JtDatagramPacket;
import de.sssm.jt.raw.socket.JtDatagramSocket;
import java.util.concurrent.CountDownLatch;

/**
 *
 * @author sven
 */
public class Sender implements Runnable {

    private final static int REPEAT_COUNT = 3;
    public final static int STARTING_TTL = 1;

    private final JtDatagramSocket senderSocket;
    private final String target;
    private final int basePort;
    private final CountDownLatch lock;
    
    public Sender(JtDatagramSocket senderSocket, final String target, final int basePort, CountDownLatch lock) {
        this.senderSocket = senderSocket;
        this.senderSocket.open();
        this.target = target;
        this.basePort = basePort;
        this.lock = lock;
    }
    
    @Override
    public void run() {
        for(int i = STARTING_TTL; i < 30; i++){
            senderSocket.setTtl(i);
            JtDatagramPacket jtDatagramPacket = new JtDatagramPacket(new byte[0], "", 0, target, basePort + i);
            for(int j = 0; j < REPEAT_COUNT; j++){
                senderSocket.sendto(jtDatagramPacket);
            }
        }
        lock.countDown();
    }
    
}

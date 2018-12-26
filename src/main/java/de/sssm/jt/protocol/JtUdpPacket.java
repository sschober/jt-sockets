/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package de.sssm.jt.protocol;

import java.math.BigInteger;
import java.util.Arrays;

/**
 *
 * @author sven
 */
public class JtUdpPacket {
    private final int sourcePort;

    public int getSourcePort() {
        return sourcePort;
    }

    public int getDestPort() {
        return destPort;
    }

    public byte[] getPayload() {
        return payload;
    }
    private final int destPort;
    private final byte[] payload;
    
    private JtUdpPacket(final int sourcePort, final int destPort, final byte[] payload){
        this.sourcePort = sourcePort;
        this.destPort = destPort;
        this.payload = payload;
    }
    
    public static JtUdpPacket fromBytes(final byte[] bytes){

        int sourcePort = ((bytes[0] << 8) & 0xff00 ) | (bytes[1] & 0xff);
        //System.err.println(String.format("source port bytes: %2x %2x", bytes[0], bytes[1]));
        
        int destPort = ((bytes[3] << 8) & 0xff00) | (bytes[2] & 0xff);
        //System.err.println(String.format("dest port bytes: %2x %2x", bytes[2], bytes[3]));

        byte[] payload = Arrays.copyOfRange(bytes, 4, bytes.length);

        return new JtUdpPacket(sourcePort, destPort, payload);
    }
}

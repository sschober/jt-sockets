/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package de.sssm.jt.protocol;

import java.util.Arrays;

/**
 *
 * @author sven
 */
public class JtIcmpPacket {

    private static final int ICMP_HEADER_SIZE = 8;
    private int type;
    private int code;
    byte[] payload;

    public byte[] getPayload() {
        return payload;
    }
    
    public static JtIcmpPacket fromBytes(byte[] bytes) throws NoPacketException{
        JtIcmpPacket result = new JtIcmpPacket();
        if(bytes.length < 2){
            throw new NoPacketException("not enough header bytes: " + bytes.length);
        }
        result.type = bytes[0];
        System.err.println("icmp type: " + result.type);
        result.code = bytes[1];
        System.err.println("icmp code: " + result.code);
        //System.err.println("remaining bytes: " + (bytes.length - ICMP_HEADER_SIZE));
        result.payload = Arrays.copyOfRange(bytes, ICMP_HEADER_SIZE, bytes.length);
        return result;
    }
}

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
public class JtIpPacket {
    int version;
    int headerLength;
    byte[] payload;

    public static JtIpPacket fromBytes(byte[] bytes) throws NoPacketException{
        JtIpPacket result = new JtIpPacket();
        if(bytes.length > 20 ){
            // on mac os the first byte seems to be left in network order, so
            // the version is the higher part of the byte (should be lower) and
            // the headerLength are the lower (should be higher).
            result.version = (bytes[0] & 0xf0) >> 4;
            //System.err.println("version: " + result.version);
            result.headerLength = (bytes[0] & 0xf) * 4;
            //System.err.println("header length: " + result.headerLength);
            if(result.headerLength < bytes.length){
                result.payload = Arrays.copyOfRange(bytes, result.headerLength, bytes.length-1);
            }
            else{
                throw new NoPacketException("illegal header size: " + result.headerLength);
            }
        }
        else{
            throw new NoPacketException("not enough bytes for header: " + bytes.length);
        }
        //System.err.println("created ip packet with header length " + result.headerLength + " and payload size of " + result.payload.length);
        return result;
    }
    
    public byte[] getPayload(){
        return payload;
    }

}

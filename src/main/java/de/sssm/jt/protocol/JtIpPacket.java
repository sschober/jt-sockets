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
    byte typeOfService;
    byte timeToLive;
    byte protocol;
    byte[] payload;

    public static JtIpPacket fromBytes(byte[] bytes) throws NoPacketException{
        JtIpPacket result = new JtIpPacket();
        if(bytes.length > 20 ){
            // on mac os the first byte seems to be left in network order, so
            // the version is the higher part of the byte (should be lower) and
            // the headerLength are the lower (should be higher).
            result.version = (bytes[0] & 0xf0) >> 4;
            System.err.print("version: " + result.version);
            result.headerLength = (bytes[0] & 0xf) * 4;
            System.err.print(", header length: " + result.headerLength);
            result.typeOfService = bytes[1];
            System.err.print(", type of service: " + result.typeOfService);
            result.timeToLive = bytes[8];
            System.err.print(", time to live: " + result.timeToLive);
            result.protocol = bytes[9];
            System.err.println(", protocol: " + result.protocol);
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

    public byte getProtocol(){
        return protocol;
    }
}

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package de.sssm.jt.raw.socket;

/**
 * Data object representing a datagram packet
 * @author sven
 */
public class JtDatagramPacket {
    final byte[] bytes;
    final String sourceAddress;
    final int sourcePort;
    final String destAddress;
    final int destPort;

    public JtDatagramPacket(byte[] bytes, String sourceAddress, int sourcePort, String destAddress, int destPort) {
        this.bytes = bytes;
        this.sourceAddress = sourceAddress;
        this.sourcePort = sourcePort;
        this.destAddress = destAddress;
        this.destPort = destPort;
    }  
}

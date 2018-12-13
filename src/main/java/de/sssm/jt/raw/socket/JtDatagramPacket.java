/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package de.sssm.jt.raw.socket;

/**
 *
 * @author sven
 */
public class JtDatagramPacket {
    final byte[] bytes;
    final String sourceAddress;
    final int sourcePort;

    public JtDatagramPacket(byte[] bytes, String sourceAddress, int sourcePort) {
        this.bytes = bytes;
        this.sourceAddress = sourceAddress;
        this.sourcePort = sourcePort;
    }  
}

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package de.sssm.jt.raw.socket;

import java.net.InetAddress;
import java.net.UnknownHostException;

/**
 * Data object representing a datagram packet
 * 
 * @author sven
 */
public class JtDatagramPacket {
    public final byte[] bytes;
    public final String sourceAddress;
    public final int sourcePort;
    public final String destAddress;
    public final int destPort;

    private JtDatagramPacket(byte[] bytes, String sourceAddress, int sourcePort, String destAddress, int destPort) {
        this.bytes = bytes;
        this.sourceAddress = sourceAddress;
        this.sourcePort = sourcePort;
        this.destAddress = destAddress;
        this.destPort = destPort;
    }

    /**
     * Constructs a {@link JtDatagramPacket} from the arguments given.
     * <p/>
     * Special consideration to the address parts is given: the
     * address might be passed as a hostname, or as a numerical IP
     * address, the first form is tried to resolve to the numerical
     * form.
     * <p/>
     * The resulting packet will always contain addresses in
     * numerical form. 
     */
    public static JtDatagramPacket of(byte[] bytes, String sourceAddress, int sourcePort, String destAddress,
            int destPort) throws UnknownHostException {
        InetAddress sourceInetAddress = null;
        if(!sourceAddress.isEmpty()){
            sourceInetAddress = InetAddress.getByName(sourceAddress);
        }
        else {
            sourceInetAddress = InetAddress.getLocalHost();
        }
        InetAddress targetInetAddress = null;
        if(!destAddress.isEmpty()){
            targetInetAddress = InetAddress.getByName(destAddress);
        }
        return new JtDatagramPacket(bytes, sourceInetAddress.getHostAddress(), sourcePort, targetInetAddress.getHostAddress(), destPort);
    }
}

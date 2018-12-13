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
public class JtDatagramSocket extends JtAbstractSocket {
    protected native void _sayHello();
    protected native int _open();
    protected native void _close(int fd);    
    protected native JtDatagramPacket _recvfrom(int fd);

}

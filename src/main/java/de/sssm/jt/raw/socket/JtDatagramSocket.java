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
    protected native int _open();
    protected native JtDatagramPacket _recvfrom(int fd);

    protected native void _sendto(int fd, String destAddress, int destPort, byte[] bytes);
    public void sendto(JtDatagramPacket p){
        _sendto(fd, p.destAddress, p.destPort, p.bytes);
    }
    
    protected native void _setTtl(int fd, int ttl);
    public void setTtl(int ttl){
        _setTtl(fd, ttl);
    }
    
    public static void main(String[] args) {
        String target = "172.217.21.35"; // google.de
        
        JtDatagramSocket jtDatagramSocket = new JtDatagramSocket();
        JtDatagramPacket jtDatagramPacket = new JtDatagramPacket(new byte[0], "", 0, target, 55555);
        
        jtDatagramSocket.open();
        jtDatagramSocket.setTtl(2);
        jtDatagramSocket.sendto(jtDatagramPacket);
        
    }
  
}

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package de.sssm.jt.raw.socket;

/**
 *
 * @author Sven Schober <sschober@sssm.de>
 */
public class JtRawSocket extends JtAbstractSocket{

    protected native void _sayHello();
    protected native int _open();
    protected native void _close(int fd);    
    protected native JtDatagramPacket _recvfrom(int fd);
      
    public static void main(String[] args) throws SocketNotOpenException {
        JtRawSocket jtRawSocket = new JtRawSocket();
        
        jtRawSocket.sayHello();
        jtRawSocket.open();
        
// do stuff
        JtDatagramPacket result = jtRawSocket.recvfrom();
        
        System.out.println("received: " + result.bytes.length + " bytes from: " + result.sourceAddress + ":" + result.sourcePort);
        
        StringBuilder sb = new StringBuilder();
        for(byte b: result.bytes){
            sb.append(String.format("%02X ",b));
        }
        System.out.println(sb.toString());

        jtRawSocket.close();
    }

    
}

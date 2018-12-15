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
public abstract class JtAbstractSocket {
    // file descriptor of native socket
    protected int fd = -1;
    
    static {
        System.loadLibrary("native");
    }

    private native void _sayHello();
    private native void _close(int fd);    
    
    protected abstract int _open();
    protected abstract JtDatagramPacket _recvfrom(int fd);
    
    public void sayHello(){
        _sayHello();
    }
    
    public void open(){
        fd = _open();
    }

    public void close() throws SocketNotOpenException{
        if(fd>0){
            _close(fd);
        }
        else{
            throw new SocketNotOpenException();
        }
    }

    public JtDatagramPacket recvfrom(){
        return _recvfrom(fd);
    }
}

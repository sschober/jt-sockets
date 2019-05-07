/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package de.sssm.jt.raw.socket;

import de.sssm.jt.NarSystem;
/**
 *
 * @author sven
 */
public abstract class JtAbstractSocket {
    // file descriptor of native socket
    protected int fd = -1;
    
    static {
        NarSystem.loadLibrary();
        // on windows we need to init the winsock library
        _init();
    }

    private native void _close(int fd);    
    protected abstract int _open();
    protected abstract JtDatagramPacket _recvfrom(int fd) throws JtReceiveTimeoutException;
    protected native static void _init();

    public void open(){
        fd = _open();
    }

    public void close() throws JtSocketNotOpenException{
        if(fd>0){
            _close(fd);
        }
        else{
            throw new JtSocketNotOpenException();
        }
    }

    private native void _bind(int fd, String localAddress, int port);
    public void bind(String localAddress, int port){
        _bind(fd, localAddress, port);
    }

    public JtDatagramPacket recvfrom() throws JtReceiveTimeoutException{
        return _recvfrom(fd);
    }

    protected native void _setTtl(int fd, int ttl);
    public void setTtl(int ttl){
        _setTtl(fd, ttl);
    }
    
}

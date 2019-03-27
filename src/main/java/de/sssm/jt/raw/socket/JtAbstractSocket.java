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
        // TODO: NetBeans does not see this class
        NarSystem.loadLibrary();
    }

    private native void _sayHello();
    private native void _close(int fd);    
    
    protected abstract int _open();
    protected abstract JtDatagramPacket _recvfrom(int fd) throws JtReceiveTimeoutException;
    
    public void sayHello(){
        _sayHello();
    }
    
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

    public JtDatagramPacket recvfrom() throws JtReceiveTimeoutException{
        return _recvfrom(fd);
    }
}

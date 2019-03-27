/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package de.sssm.jt.protocol;

/**
 *
 * @author sven
 */
public class NoPacketException extends Exception{

    private static final long serialVersionUID = 1L;

    NoPacketException(String string) {
        super(string);
    }
    
}

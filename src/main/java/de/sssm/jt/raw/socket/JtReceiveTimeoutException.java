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
public class JtReceiveTimeoutException extends Exception {
    public JtReceiveTimeoutException(String message){
        super(message);
    }
}

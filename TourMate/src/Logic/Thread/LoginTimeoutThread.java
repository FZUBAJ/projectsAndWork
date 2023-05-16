package Logic.Thread;

import GUI.loginForm;


public class LoginTimeoutThread extends Thread{
    private loginForm loginFormInstance;

    public LoginTimeoutThread(loginForm loginFormInstance){
        this.loginFormInstance = loginFormInstance;
    }

    @Override
    public void run(){
        try{
            System.out.println("Login timeout thread started");
            Thread.sleep(120000);
            System.out.println("Login timeout thread finished");

            if(loginFormInstance.isVisible()){
                loginFormInstance.dispose();
                System.exit(0);
            }
        } catch(InterruptedException e){
            e.printStackTrace();
        }
    }
}




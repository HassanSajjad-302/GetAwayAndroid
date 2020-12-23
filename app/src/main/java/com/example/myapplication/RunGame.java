package com.example.myapplication;

public class RunGame extends Thread{
    MainActivity mainActivity;
    RunGame(MainActivity activity){
        mainActivity = activity;
    }
    public void run(){
        mainActivity.startGame();
    }
}

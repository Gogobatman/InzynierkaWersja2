package com.example.kostkaledowa;

import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.Charset;
import java.util.Set;
import java.util.UUID;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.graphics.Color;
import android.os.Bundle;
import android.support.v4.content.LocalBroadcastManager;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity implements OnClickListener {

    TextView t1;
    TextView textView2;

    String address = null, name = null;
    InputStream inputStream=null;
    BluetoothAdapter myBluetooth = null;
    BluetoothSocket btSocket = null;
    Set<BluetoothDevice> pairedDevices;
    static final UUID myUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    final int[][][] idArray = {
            {
                    {R.id.radioButton111, R.id.radioButton211, R.id.radioButton311, R.id.radioButton411},
                    {R.id.radioButton121, R.id.radioButton221, R.id.radioButton321, R.id.radioButton421},
                    {R.id.radioButton131, R.id.radioButton231, R.id.radioButton331, R.id.radioButton431},
                    {R.id.radioButton141, R.id.radioButton241, R.id.radioButton341, R.id.radioButton441},
            },
            {
                    {R.id.radioButton112, R.id.radioButton212, R.id.radioButton312, R.id.radioButton412},
                    {R.id.radioButton122, R.id.radioButton222, R.id.radioButton322, R.id.radioButton422},
                    {R.id.radioButton132, R.id.radioButton232, R.id.radioButton332, R.id.radioButton432},
                    {R.id.radioButton142, R.id.radioButton242, R.id.radioButton342, R.id.radioButton442},
            },
            {
                    {R.id.radioButton113, R.id.radioButton213, R.id.radioButton313, R.id.radioButton413},
                    {R.id.radioButton123, R.id.radioButton223, R.id.radioButton323, R.id.radioButton423},
                    {R.id.radioButton133, R.id.radioButton233, R.id.radioButton333, R.id.radioButton433},
                    {R.id.radioButton143, R.id.radioButton243, R.id.radioButton343, R.id.radioButton443},
            },
            {
                    {R.id.radioButton114, R.id.radioButton214, R.id.radioButton314, R.id.radioButton414},
                    {R.id.radioButton124, R.id.radioButton224, R.id.radioButton324, R.id.radioButton424},
                    {R.id.radioButton134, R.id.radioButton234, R.id.radioButton334, R.id.radioButton434},
                    {R.id.radioButton144, R.id.radioButton244, R.id.radioButton344, R.id.radioButton444},
            }
    };
    static Button radiobutton[][][] = new Button[10][10][10];
    char matrix[][][] = new char[10][10][10];
    boolean win = false;
    boolean connected = false;

    String temp1="0";
    String temp2="0";
    String temp3="0";
    public void declareButtons() {
        for (int z = 0; z < 4; z++) {
            for (int y = 0; y < 4; y++) {
                for (int x = 0; x < 4; x++) {
                    radiobutton[z][y][x] = (Button) findViewById(idArray[z][y][x]);
                    radiobutton[z][y][x].setBackgroundColor(Color.parseColor("#D3D3D3"));
                }
            }
        }
    }

    public void cleanMatrix() {
        for (int z = 0; z < 4; z++) {
            for (int y = 0; y < 4; y++) {
                for (int x = 0; x < 4; x++) {
                    matrix[z][y][x] = ' ';
                }
            }
        }
    }
        public void checkIfWin(char znak) {
        for (int z = 0; z < 4; z++) {
            for (int y = 0; y < 4; y++) {
                for (int x = 0; x < 4; x++) {
                    if (((matrix[z][y][x] == znak) && (matrix[z][y][x + 1] == znak) &&
                            (matrix[z][y][x + 2] == znak) && (matrix[z][y][x + 3] == znak)) ||
                            ((matrix[z][y][x] == znak) && (matrix[z][y + 1][x] == znak) &&
                                    (matrix[z][y + 2][x] == znak) && (matrix[z][y + 3][x] == znak)) ||
                            ((matrix[z][y][x] == znak) && (matrix[z + 1][y][x] == znak) &&
                                    (matrix[z + 2][y][x] == znak) && (matrix[z + 3][y][x] == znak)) ||
                            (((matrix[z][y][x] == znak) && (matrix[z + 1][y + 1][x + 1] == znak) &&
                                    (matrix[z + 2][y + 2][x + 2] == znak) && (matrix[z + 3][y + 3][x + 3] == znak))) ||
                            (((matrix[z][y][x + 3] == znak) && (matrix[z + 1][y + 1][x + 2] == znak) &&
                                    (matrix[z + 2][y + 2][x + 1] == znak) && (matrix[z + 3][y + 3][x] == znak))) ||
                            (((matrix[z][y + 3][x] == znak) && (matrix[z + 1][y + 2][x + 1] == znak) &&
                                    (matrix[z + 2][y + 1][x + 2] == znak) && (matrix[z + 3][y][x + 3] == znak))) ||
                            (((matrix[z + 3][y][x] == znak) && (matrix[z + 2][y + 1][x + 1] == znak) &&
                                    (matrix[z + 1][y + 2][x + 2] == znak) && (matrix[z][y + 3][x + 3] == znak)))) {
                        win = true;
                        textView2.setText("wygrales " + znak);
                    }

                }
            }
        }
    }


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        declareButtons();
        cleanMatrix();
        t1 = (TextView) findViewById(R.id.textView1);
        textView2 = (TextView) findViewById(R.id.textView2);
        try {
            bluetooth_connect_device();
        } catch (IOException e) {
            System.out.print(e);
        }
    }


    public void doSomething(View v) {
        if (isEndOfGame()) {
            return;
        }

        for (int z = 0; z < 4; z++) {
            for (int y = 0; y < 4; y++) {
                for (int x = 0; x < 4; x++) {
                    if (v.getId() == idArray[z][y][x]) {
                        if (matrix[z][y][x] != 'R' && matrix[z][y][x] != 'G' && matrix[z][y][x] != 'B') {


                            temp1=Integer.toString(x+1);
                            temp2=Integer.toString(y+1);
                            temp3=Integer.toString(z+1);
                            led_on_off(temp3+temp2+temp1);
                            receiveData();


                           // matrix[z][y][x] = 'R';
                            //radiobutton[z][y][x].setBackgroundColor(Color.RED);
                           // checkIfWin('R');
                        }
                    }
                }
            }
        }
    }

    private boolean isEndOfGame() {
        return !connected || win;
    }

    private void bluetooth_connect_device() throws IOException {
        try {
            myBluetooth = BluetoothAdapter.getDefaultAdapter();
            address = myBluetooth.getAddress();
            pairedDevices = myBluetooth.getBondedDevices();
            if (pairedDevices.size() > 0) {
                for (BluetoothDevice bt : pairedDevices) {
                    address = bt.getAddress().toString();
                    name = bt.getName().toString();
                    Toast.makeText(getApplicationContext(), "Connected", Toast.LENGTH_SHORT).show();
                    connected = true;

                }
            }

        } catch (Exception we) {
        }
        myBluetooth = BluetoothAdapter.getDefaultAdapter();//get the mobile bluetooth device
        BluetoothDevice dispositivo = myBluetooth.getRemoteDevice(address);//connects to the device's address and checks if it's available
        btSocket = dispositivo.createInsecureRfcommSocketToServiceRecord(myUUID);//create a RFCOMM (SPP) connection
        btSocket.connect();

        try {
            t1.setText("BT Name: " + name + "\nBT Address: " + address);
        } catch (Exception e) {
        }
    }

    @Override
    public void onClick(View v) {
        try {

        } catch (Exception e) {
            Toast.makeText(getApplicationContext(), e.getMessage(), Toast.LENGTH_SHORT).show();

        }

    }

    private void led_on_off(String i) {
        try {
            if (btSocket != null) {

                btSocket.getOutputStream().write(i.toString().getBytes());


            }

        } catch (Exception e) {
            Toast.makeText(getApplicationContext(), e.getMessage(), Toast.LENGTH_SHORT).show();

        }

    }
    public void receiveData(){
        byte[] buffer = new byte[1024];  // buffer store for the stream

        int bytes; // bytes returned from read()

        // Keep listening to the InputStream until an exception occurs

            // Read from the InputStream
            try {
                inputStream = btSocket.getInputStream();
                bytes = inputStream.read(buffer);
                String incomingMessage = new String(buffer, 0, bytes);
                char[] matrix2 = incomingMessage.toCharArray();
                //matrix translation
                matrix[0][0][0]=matrix2[0];
                matrix[1][0][0]=matrix2[1];
                matrix[2][0][0]=matrix2[2];
                matrix[3][0][0]=matrix2[3];

                matrix[0][1][0]=matrix2[4];
                matrix[1][1][0]=matrix2[5];
                matrix[2][1][0]=matrix2[6];
                matrix[3][1][0]=matrix2[7];

                matrix[0][2][0]=matrix2[8];
                matrix[1][2][0]=matrix2[9];
                matrix[2][2][0]=matrix2[10];
                matrix[3][2][0]=matrix2[11];

                matrix[0][3][0]=matrix2[12];
                matrix[1][3][0]=matrix2[13];
                matrix[2][3][0]=matrix2[14];
                matrix[3][3][0]=matrix2[15];
                ////////////////////////////
                matrix[0][0][1]=matrix2[16];
                matrix[1][0][1]=matrix2[17];
                matrix[2][0][1]=matrix2[18];
                matrix[3][0][1]=matrix2[19];

                matrix[0][1][1]=matrix2[20];
                matrix[1][1][1]=matrix2[21];
                matrix[2][1][1]=matrix2[22];
                matrix[3][1][1]=matrix2[23];

                matrix[0][2][1]=matrix2[24];
                matrix[1][2][1]=matrix2[25];
                matrix[2][2][1]=matrix2[26];
                matrix[3][2][1]=matrix2[27];

                matrix[0][3][1]=matrix2[28];
                matrix[1][3][1]=matrix2[29];
                matrix[2][3][1]=matrix2[30];
                matrix[3][3][1]=matrix2[31];
                ////////////////////////////
                matrix[0][0][2]=matrix2[32];
                matrix[1][0][2]=matrix2[33];
                matrix[2][0][2]=matrix2[34];
                matrix[3][0][2]=matrix2[35];

                matrix[0][1][2]=matrix2[36];
                matrix[1][1][2]=matrix2[37];
                matrix[2][1][2]=matrix2[38];
                matrix[3][1][2]=matrix2[39];

                matrix[0][2][2]=matrix2[40];
                matrix[1][2][2]=matrix2[41];
                matrix[2][2][2]=matrix2[42];
                matrix[3][2][2]=matrix2[43];

                matrix[0][3][2]=matrix2[44];
                matrix[1][3][2]=matrix2[45];
                matrix[2][3][2]=matrix2[46];
                matrix[3][3][2]=matrix2[47];
                ////////////////////////////
                matrix[0][0][3]=matrix2[48];
                matrix[1][0][3]=matrix2[49];
                matrix[2][0][3]=matrix2[50];
                matrix[3][0][3]=matrix2[51];

                matrix[0][1][3]=matrix2[52];
                matrix[1][1][3]=matrix2[53];
                matrix[2][1][3]=matrix2[54];
                matrix[3][1][3]=matrix2[55];

                matrix[0][2][3]=matrix2[56];
                matrix[1][2][3]=matrix2[57];
                matrix[2][2][3]=matrix2[58];
                matrix[3][2][3]=matrix2[59];

                matrix[0][3][3]=matrix2[60];
                matrix[1][3][3]=matrix2[61];
                matrix[2][3][3]=matrix2[62];
                matrix[3][3][3]=matrix2[63];
                ////////////////////////////
                refreshGame();
                checkIfWin('R');
                //
            } catch (IOException e) {

            }

    }
    public void refreshGame(){
        for(int z=0; z<4; z++){
            for(int y=0; y<4; y++){
                for(int x=0;x>4;x++){
                    radiobutton[z][y][x].setBackgroundColor(Color.parseColor("#D3D3D3"));
                    if(matrix[z][y][x]=='R'){
                        radiobutton[z][y][x].setBackgroundColor(Color.RED);
                    }else if(matrix[z][y][x]=='G'){
                        radiobutton[z][y][x].setBackgroundColor(Color.GREEN);
                    }if(matrix[z][y][x]=='B'){
                        radiobutton[z][y][x].setBackgroundColor(Color.BLUE);
                    }
                }
            }
        }
    }
}

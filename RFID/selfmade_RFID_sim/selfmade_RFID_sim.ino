#include <stdio.h>
#include <EEPROM.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sleep.h>

// uncomment the following line to get debug information dumped
#define SERIALDEBUG


/***************************************************************************
 *                                                                         *
 *  A Universal RFID Key - Instructables Version                           *
 *                                                                         *
 *   Copyright (C) 2010  Doug Jackson (doug@doughq.com)                    *
 *                                                                         *
 ***************************************************************************
 *                                                                         * 
 * This program is free software; you can redistribute it and/or modify    *
 * it under the terms of the GNU General Public License as published by    *
 * the Free Software Foundation; either version 2 of the License, or       *
 * (at your option) any later version.                                     *
 *                                                                         *
 * This program is distributed in the hope that it will be useful,         *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 * GNU General Public License for more details.                            *
 *                                                                         *
 * You should have received a copy of the GNU General Public License       *
 * along with this program; if not, write to the Free Software             *
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,                   *
 * MA  02111-1307  USA                                                     *
 *                                                                         *
 ***************************************************************************
 *                                                                         *
 *    * * * * * * * *      W A R N I N G     * * * * * * * * * *           *
 * This project implements what is effectively a universal skeleton key    *
 * for use on a range of RFID access systems.  It is presented for         *
 * educational and demonstration purposes only to enable others to learn   *
 * about the design and limitations of RFID technologies.                  *
 *                                                                         *
 * The Author is not responsible for misuse of the technological system    *
 * implemented by this software - USE AT YOUR OWN RISK!!                   *
 *                                                                         *
 ***************************************************************************
 *
 * 
 * Revision History
 * 
 * Date  	By	What
 * 20101002	DRJ	Initial Creation of Arduino Version 
 * 20101024     DRJ     Added facility to arbitrarily enter a facility and 
 *                      UserID number
 * 20101025     DRJ     Added ability to enter decimal UserID
 * 20101124     DRJ     Removed my Work specific functions for public release
 ***************************************************************************
 * 
 *  COMMAND STRUCTURE
 *
 * Mode key is pressed until appropriate mode is displayed on 4 upper leds
 * Enter key triggers action
 *
 * Mode 1 - Sleep (power down till next reset)
 * Mode 2 - Allow HEX facility code to be entered 
 *          2 decimal characters are then read into facility[] array;
 * Mode 3 - Allow Decimal userID to be entered
 *          8 decimal characters are then read into user[] array;
 * Mode 4 - Dump data - Facility code and User code are output on 4 LEDs one byte at a time
 * Mode 5 - Emulate Card
 *
 *
 *************************************************************************************/

#define DATALED1 0
#define DATALED2 1
#define DATALED3 2
#define DATALED4 3
#define STATUSLED1 8
#define STATUSLED2 9

// the Coil is connected to Analog 5 = Digital 19
#define COIL 19


byte facility[2]={ 0x02, 0x0C };
byte cardID[8]={ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
int colsum[4]={ 0,0,0,0}; // storage for the column checksums

// delay between symbols when we are transmitting
int bittime=256;

byte RFIDdata[128];

int clock=0;  // storage for the current state of our clock signal.

byte datapointer=0;
byte state;
byte mode=1;


void setup()
{

  pinMode(DATALED1, OUTPUT); 
  pinMode(DATALED2, OUTPUT); 
  pinMode(DATALED3, OUTPUT);  
  pinMode(DATALED4, OUTPUT); 
  pinMode(STATUSLED1, OUTPUT); 
  pinMode(STATUSLED2, OUTPUT); 


  pinMode(COIL, OUTPUT);
  //Start with it LOW  
  digitalWrite(COIL, LOW);

  if (EEPROM.read(0)==0xa5)
  {
      facility[0]=EEPROM.read(1);
      facility[1]=EEPROM.read(2);
      
      cardID[0]=EEPROM.read(3);
      cardID[1]=EEPROM.read(4);
      cardID[2]=EEPROM.read(5);
      cardID[3]=EEPROM.read(6);
      cardID[4]=EEPROM.read(7);
      cardID[5]=EEPROM.read(8);
      cardID[6]=EEPROM.read(9);
      cardID[7]=EEPROM.read(10);
  }
  else
 {
    EEPROM.write(0,0xa5);
    facility[0]=0x02; EEPROM.write(1,facility[0]);  
    facility[1]=0x0c; EEPROM.write(2,facility[1]);
      for (int i=0; i<8; i++) 
    {
      cardID[i]=0; EEPROM.write(i+2,cardID[i]);
    }
  }
    

    #ifdef SERIALDEBUG 
    Serial.begin(9600);  
    delay(200);
    Serial.println("  ");
    Serial.println("RFID Spoofer (c) 2010 D Jackson"); 
    #endif
}

void WriteHeader(void)
{
  // a header consists of 9 one bits
  RFIDdata[datapointer++]=1; 
  RFIDdata[datapointer++]=1;  
  RFIDdata[datapointer++]=1;  
  RFIDdata[datapointer++]=1; 
  RFIDdata[datapointer++]=1; 
  RFIDdata[datapointer++]=1; 
  RFIDdata[datapointer++]=1; 
  RFIDdata[datapointer++]=1; 
  RFIDdata[datapointer++]=1; 
}


void WriteData(byte nibble)
{
  byte data;
  byte rowsum=0;
  for (int i=4; i>0; i--)
  {
    if ((nibble& 1<<i-1) ==0)  
    {
      data=0; 
    }
    else 
    {
      data=1;
      rowsum++;  // increment the checksum value
      colsum[i-1]++; // increment the column checksum
    }


    RFIDdata[datapointer++]= data;
    #ifdef SERIALDEBUG 
      Serial.print((int) data); 
    #endif
     
  }
  // write the row checksum out
  if ((rowsum%2)==0)  
  {
    RFIDdata[datapointer++]=0; 
    #ifdef SERIALDEBUG 
      Serial.print((int)0); 
    #endif
    
  }
  else
  {  
    RFIDdata[datapointer++]=1; 
    #ifdef SERIALDEBUG 
      Serial.print((int)1); 
    #endif
  }

    #ifdef SERIALDEBUG 
      Serial.println(); 
    #endif

}


void WriteChecksum(void)
{
  byte data;
  byte rowsum=0;
  for (int i=4; i>0; i--)
  {
    if ((colsum[i-1]%2) ==0)  
    {
      RFIDdata[datapointer++]=0; 
     #ifdef SERIALDEBUG 
      Serial.print((int)0); 
     #endif
    }
    else
    {
      RFIDdata[datapointer++]=1; 
      #ifdef SERIALDEBUG 
      Serial.print((int) 1); 
      #endif
    }  
  }

  // write the stop bit
  RFIDdata[datapointer++]=0; 

      #ifdef SERIALDEBUG 
      Serial.print((int)0); 
      #endif

}





void BuildCard(void)
{
  // load up the RFID array with card data
  // intitalise the write pointer
  datapointer=0;

  WriteHeader();
  // Write facility
  WriteData(facility[0]);
  WriteData(facility[1]);
 
  // Write cardID
  WriteData(cardID[0]);
  WriteData(cardID[1]);
  WriteData(cardID[2]);
  WriteData(cardID[3]);
  WriteData(cardID[4]);  
  WriteData(cardID[5]);
  WriteData(cardID[6]);  
  WriteData(cardID[7]);

  WriteChecksum();
}


void TransmitManchester(int cycle, int data)
{

  if(cycle ^ data == 1)
  {
    digitalWrite(COIL, HIGH);
  }
  else
  {
    digitalWrite(COIL, LOW);  
  }
}


void EmulateCard(void)
{
  #ifdef SERIALDEBUG 
  Serial.println("Emulate Card Entered"); 
  #endif  // enter a low power modewritedataLEDS(0);  // turn off the LEDs
  
  BuildCard();
  
  #ifdef SERIALDEBUG 
  Serial.println(); 
  for(int i = 0; i < 64; i++)
  {
    if (RFIDdata[i]==1) Serial.print("1"); 
    else if (RFIDdata[i]==0) Serial.print("0"); 
    else Serial.print((int)RFIDdata[i]); 
  } 
  Serial.println(); 
  #endif  
  

  while (1==1)
  {
    for(int i = 0; i < 64; i++)
    {
      TransmitManchester(0, RFIDdata[i]);
      delayMicroseconds(bittime);
      TransmitManchester(1, RFIDdata[i]);
      delayMicroseconds(bittime); 
    } 
  }
}

void loop(void){
  EmulateCard();  // start card emulation
}

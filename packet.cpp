//--------------------------------------------------------------------
//
//  Laboratory 4, In-lab Exercise 1                       packet.cpp
//
//  SOLUTION: Message packet processing program
//
//--------------------------------------------------------------------

#include <iostream>
#include <fstream>

using namespace std;

#include "OrderedList.cpp"

// Reads a series of packets, formats them into a message, and
// outputs the message.

class Packet {
  public:
    static const int PACKET_SIZE = 6;  // Number of characters in a packet
                               // including null ('\0') terminator,
                               // but excluding the key (1st char in each line).
    int position;              // (Key) Packet's position w/in message
    char body[PACKET_SIZE];    // Characters in the packet

    int getKey () const
        { return position; }   // Returns the key field
};

//--------------------------------------------------------------------

int main()
{
    ifstream messageFile ("message.dat");   // Message file
    OrderedList<Packet,int> message;        // Message
    Packet currPacket;                      // Message packet
    int j;                                  // Loop variable

    // Read in the message.

    currPacket.body[Packet::PACKET_SIZE-1] = '\0';
    while ( messageFile >> currPacket.position )
    {
        messageFile.getline(currPacket.body,Packet::PACKET_SIZE,'\n');

        // I/O problem could happen during getline. 
        // Check that I/O problem-free before inserting packet.
        if ( messageFile )  
            message.insert(currPacket);
    }

    // Output the message packet-by-packet.

    cout << endl << "Message:" << endl;
    if( message.isEmpty() == false) {
	message.gotoBeginning();
	do
	{
	    currPacket = message.getCursor();
	    cout << currPacket.body;
	}
	while ( message.gotoNext() );
	cout << endl;
    }

    return 0;
}


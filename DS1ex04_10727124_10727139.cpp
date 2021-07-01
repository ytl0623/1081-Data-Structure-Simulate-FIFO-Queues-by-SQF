// 10727124 劉宇廷 10727139 蘇崇傑

#include <iostream>
#include <cstdio>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
using namespace std;

double maxi;     // 工作數量
typedef char Str80 [80];

struct Item {
  int id;     // 工作編號
  int arrival;     // 進入時刻
  int duration;     // 花費時間
  int timeout;     //截止時刻
  int start;     // 起始時刻
  
};

struct Abort {     // 取消清單
  int num;     //
  int id;     // 工作編號
  int cancel;     // 取消時刻
  int delay;     // 延遲時間
  
};

struct Done {     // 成功清單
  int num;     //
  int id;     // 工作編號
  int departure;     // 完成時刻
  int delay;     // 延遲時間
  
};

void Swap( Item & a, Item & b ){
  int temp;
  
  temp = a.id;
  a.id = b.id;
  b.id = temp;
  
  temp = a.arrival;
  a.arrival = b.arrival;
  b.arrival = temp;
  
  temp = a.duration;
  a.duration = b.duration;
  b.duration = temp;
  
  temp = a.timeout;
  a.timeout = b.timeout;
  b.timeout = temp;
  
}

bool Readcom1( string command, Item *arrays ){     // Read input.txt
  string filename = "input" + command + ".txt";
  FILE *infile = NULL;  
  infile = fopen( filename.c_str(), "r" );
  
  if ( infile == NULL ) {
    cout << endl << filename << " does not exist!\n" << endl;
    return false;
  }
  else {
    Str80 str1, str2, str3, str4;
    fscanf( infile, "%s %s %s %s", str1, str2, str3, str4 );     // 標題
	
    char temp;
    fscanf( infile, "%c" , &temp ); // 換行
	
    for ( int i = 1; fscanf( infile, "%d" , &arrays[i].id ) != EOF ; i++ ){
      fscanf( infile, "%d" , &arrays[i].arrival );
      fscanf( infile, "%d" , &arrays[i].duration );
      fscanf( infile, "%d" , &arrays[i].timeout );
      maxi = i;
      fscanf( infile, "%c" , &temp ); // 換行
    }
    return true;
  }
  
  fclose( infile );
  system( "PAUSE" );
  
}

bool Readcom2( string command, Item *arrays ){     // Read sorted.txt
  string filename;
  FILE *infile = NULL;
  filename = "sorted" + command + ".txt";
  infile = fopen( filename.c_str(), "r" );
  
  if ( infile == NULL ) {
    cout << endl << filename << " does not exist!\n" << endl;
    return false;
  }
  else {
    Str80 str1, str2, str3, str4;
    fscanf( infile, "%s %s %s %s", str1, str2, str3, str4 );     // 標題
	
    char temp ;
    fscanf( infile, "%c" , &temp ); // 換行
	
    for ( int i = 1; fscanf( infile, "%d" , &arrays[i].id ) != EOF ; i++){
      arrays[i].start = 0;
      fscanf( infile, "%d" , &arrays[i].arrival );
      fscanf( infile, "%d" , &arrays[i].duration );
      fscanf( infile, "%d" , &arrays[i].timeout );
      maxi = i;
      fscanf( infile, "%c" , &temp ); // 換行
    }
    return true;
  }
  
  fclose( infile );
  system( "PAUSE" );
  
}

void Shellsort( int n, Item arrays[50] ){
  int gap = n/2;
  int i = 0;
  
  bool stop = false;
  while( gap >= 1 && !stop ){
    stop = true;
	
    for( i = 1; i <= n - gap ; i++ ){
      if( arrays[i].arrival > arrays[ i+gap ].arrival ){
        Swap( arrays[i], arrays[ i+gap ] );
        stop = false;
      }
      else if ( arrays[i].arrival == arrays[ i+gap ].arrival ){
        if ( arrays[i].id > arrays[ i+gap ].id ){
          Swap( arrays[i], arrays[ i+gap ] );
          stop = false;
        }
      }
    }
	
    if ( gap > 1 ){
      gap = gap/2;
    }
  }
}

void Insertionsort( int n, Item *arrays ){
  for ( int i = 2 ; i <= n ; i++ ) {
	Item temp = arrays[i] ;
	int j = i - 1 ;

    while ( temp.arrival <= arrays[j].arrival && j >= 1 ){
	  if ( arrays[j].arrival == temp.arrival ){
		if ( arrays[j].id > temp.id ){
		  Swap( arrays[j+1], arrays[j] ) ;
		}  
	  }
	  else{
	    Swap( arrays[j+1], arrays[j] ) ;
	  }
	  
	  j-- ;
	}	
  }
}

int main(){
  cout << "**** Simulate FIFO Queues by SQF *****" << endl;
  cout << "* 0. Quit                            *" << endl;
  cout << "* 1. Sort a file                     *" << endl;
  cout << "* 2. Simulate one FIFO queue         *" << endl;
  cout << "**************************************" << endl;
  cout << "Input a command(0, 1, 2):";

  string command;
  cin >> command;
	
  while ( command != "0" ){
    Item arrays[1000];
    Abort aborts[1000];
	Done dones[1000];
    
    if ( command == "1" ){
      cout << "Input a file number (e.g., 401, 402, 403, ...):";
      cin  >> command;
	  
      clock_t startr = clock();
      bool readsuccess = Readcom1( command, arrays);
      clock_t endr = clock();
      double rt = endr - startr;
	  
      if( readsuccess ){
        cout << endl << "Reading data: " << rt << " ms." << endl;
        clock_t starts = clock();
        Shellsort( maxi, arrays );
        clock_t ends = clock();
        double st = ends - starts;
        cout << "Sorting data: " << st << " ms." << endl;
        
		string filename = "sorted" + command + ".txt";
        FILE *sortedfile = NULL;
        sortedfile = fopen( filename.c_str(), "w" );
		
        clock_t startw = clock();
        fprintf( sortedfile, "OID	Arrival	Duration	TimeOut\n" );
        for( int i = 1; i <= maxi ; i++){
          fprintf( sortedfile, "%d	", arrays[i].id );
          fprintf( sortedfile, "%d	", arrays[i].arrival );
          fprintf( sortedfile, "%d	", arrays[i].duration );
          fprintf( sortedfile, "%d\n", arrays[i].timeout );
        }
        clock_t endw = clock();
        double wt = endw - startw;
        cout << "Writing data: " << wt << " ms."<< endl;
        
        cout << endl << "See " << filename << endl;
 
        fclose( sortedfile );
        system( "PAUSE" );
      }
    }
    else if ( command == "2" ){
      cout << "Input a file number (e.g., 401, 402, 403, ...):";
      cin  >> command;
	  
      if( Readcom2( command, arrays ) ){
        bool que1 = true;
        bool que2 = true;
        bool que3 = true;
        int i = 5;
        int numofabort = 0;
        int numofdone = 0;
        Item cpu;
        Item queues[3];
        float delays = 0.0;
        float rate = 0.0;
        int time;
		
        Swap( cpu, arrays[1] );
        cpu.start = cpu.arrival;
        Swap( queues[1], arrays[2] );
        Swap( queues[2], arrays[3] );
        Swap( queues[3], arrays[4] );
		
        int j = 1;
		while ( j <= maxi ){
          if ( cpu.timeout >= ( cpu.start + cpu.duration ) ){
            time = cpu.start + cpu.duration;
            numofdone++;
            dones[numofdone].num = numofdone;
            dones[numofdone].id = cpu.id;
            dones[numofdone].departure = time;
            dones[numofdone].delay = cpu.start - cpu.arrival;
          }
		  else {
            time = cpu.timeout;
            numofabort++;
            aborts[numofabort].num = numofabort;
            aborts[numofabort].id = cpu.id;
            aborts[numofabort].cancel = time;
            aborts[numofabort].delay = cpu.timeout - cpu.arrival;
          }

          while ( arrays[i].arrival < time && i <= maxi ){
            numofabort++;
            aborts[numofabort].num = numofabort;
            aborts[numofabort].id = arrays[i].id;
            aborts[numofabort].cancel = arrays[i].arrival;
            aborts[numofabort].delay = 0;
            i++;
            j++;
          }

          if ( queues[1].timeout <= time && que1 ){
            numofabort++;
            aborts[numofabort].num = numofabort;
            aborts[numofabort].id = queues[1].id;
            aborts[numofabort].cancel = time;
            aborts[numofabort].delay = time - queues[1].arrival;
            que1 = false;
            j++;
			
            if ( queues[2].timeout <= time && que2 ){
              numofabort++;
              aborts[numofabort].num = numofabort;
              aborts[numofabort].id = queues[2].id;
              aborts[numofabort].cancel = time;
              aborts[numofabort].delay = time - queues[2].arrival;
              que2 = false;
              j++;
 
              if ( queues[3].timeout <= time && que3 ){
                numofabort++;
                aborts[numofabort].num = numofabort;
                aborts[numofabort].id = queues[3].id;
                aborts[numofabort].cancel = time;
                aborts[numofabort].delay = time - queues[3].arrival;
                que3 = false;
                j++;
              }
            }
          }

          if ( !que1 && !que2 && !que3 ){
            if ( i <= maxi ){
              cpu.arrival = arrays[i].arrival;
			  
              if ( cpu.arrival > time ){
                  time = cpu.arrival;
              }
			  
              cpu.start = time;
              cpu.duration = arrays[i].duration;
              cpu.id = arrays[i].id;
              cpu.timeout = arrays[i].timeout;
              i++;
            }
			
            if ( i<= maxi){
              queues[1].arrival = arrays[i].arrival;
              queues[1].duration = arrays[i].duration;
              queues[1].id = arrays[i].id;
              queues[1].timeout = arrays[i].timeout;
              que1 = true;
              i++;
            }
            else {
              que1 = false;
            }
			
            if ( i<= maxi){
              queues[2].arrival = arrays[i].arrival;
              queues[2].duration = arrays[i].duration;
              queues[2].id = arrays[i].id;
              queues[2].timeout = arrays[i].timeout;
              que2 = true;
              i++;
            }
            else {
              que2 = false;
            }
			
            if( i <= maxi ){
              queues[3].arrival = arrays[i].arrival;
              queues[3].duration = arrays[i].duration;
              queues[3].id = arrays[i].id;
              queues[3].timeout = arrays[i].timeout;
              que3 = true;
              i++;
            }
            else {
              que3 = false;
            }
          }
          else if ( !que1 && !que2 && que3 ){
            Swap( cpu, queues[3] );
			
            if ( cpu.arrival > time ){
              time = cpu.arrival;
            }
			
            cpu.start = time;
			
            if ( i <= maxi ){
              queues[1].arrival = arrays[i].arrival;
              queues[1].duration = arrays[i].duration;
              queues[1].id = arrays[i].id;
              queues[1].timeout = arrays[i].timeout;
              que1 = true;
              i++;
            }
            else {
              que1 = false;
            }
			
            if( i <= maxi ){
              queues[2].arrival = arrays[i].arrival;
              queues[2].duration = arrays[i].duration;
              queues[2].id = arrays[i].id;
              queues[2].timeout = arrays[i].timeout;
              que2 = true;
              i++;
            }
            else {
              que2 = false;
            }
			
            if ( i<= maxi){
              queues[3].arrival = arrays[i].arrival;
              queues[3].duration = arrays[i].duration;
              queues[3].id = arrays[i].id;
              queues[3].timeout = arrays[i].timeout;
              que3 = true;
              i++;
            }
			else {
              que3 = false;
            }
          }
          else if ( !que1 && que2 && que3 ){
            Swap( cpu, queues[2] );
            que2 =false;
			
            if ( cpu.arrival > time){
              time = cpu.arrival;
            }
			
            cpu.start = time;
            Swap(queues[1], queues[3]);
            que3 = false;
            que1 = true;
			
            if ( i <= maxi ){
              queues[2].arrival = arrays[i].arrival;
              queues[2].duration = arrays[i].duration;
              queues[2].id = arrays[i].id;
              queues[2].timeout = arrays[i].timeout;
              que2 = true;
              i++;
            }
            else {
              que2 = false;
            }
			
            if ( i<= maxi ){
              queues[3].arrival = arrays[i].arrival;
              queues[3].duration = arrays[i].duration;
              queues[3].id = arrays[i].id;
              queues[3].timeout = arrays[i].timeout;
              que3 = true;
              i++;
            }
			else {
              que3 = false;
            }
          }
          else if ( que1 && que2 && que3){
            Swap( cpu, queues[1] );
			
            if ( cpu.arrival > time ){
              time = cpu.arrival;
            }

            cpu.start = time;
            Swap(queues[1], queues[2]);
            Swap(queues[2], queues[3]);

			if ( i <= maxi ){
              queues[3].arrival = arrays[i].arrival;
              queues[3].duration = arrays[i].duration;
              queues[3].id = arrays[i].id;
              queues[3].timeout = arrays[i].timeout;
              que3 = true;
              i++;
            }
            else {
              que3 = false;
            }
          }
          else if ( que1 && que2 && !que3 ){
            Swap( cpu, queues[1] );
            cpu.start = time;
            Swap( queues[1], queues[2] );
            que2 = false;
          }
          else if ( que1 && !que2 && !que3 ){
            Swap(cpu, queues[1]);
            cpu.start = time;
            que1 = false;
          }
          j++;
        }

        FILE  *outfile = NULL;
        string filename = "output" + command + ".txt";
        outfile = fopen( filename.c_str(), "w" );
        fprintf(outfile, "	[Abort Jobs]\n" );
        fprintf(outfile, "	OID	Abort	Delay\n" );
		
        for ( int k = 1; k <= numofabort ; k++ ){
          fprintf( outfile, "[%d]	%d	%d	%d\n", aborts[k].num, aborts[k].id, aborts[k].cancel, aborts[k].delay );
          delays = delays + aborts[k].delay;
        }

        fprintf( outfile, "	[Jobs Done]\n" );
        fprintf( outfile, "	OID	Departure	Delay\n" );
		
        for ( int h = 1; h <= numofdone ; h++ ){
          fprintf( outfile,"[%d]	%d	%d	%d\n", dones[h].num, dones[h].id, dones[h].departure, dones[h].delay );
          delays = delays + dones[h].delay;
        }

        delays = delays / float( maxi );
        rate = float( numofdone )/ maxi * 100;
        fprintf( outfile, "[Average Delay] %.2f ms\n", delays );
        fprintf( outfile, "[Success Rate] %.2f %\n", rate );
		  
		cout << endl << "See " << filename << endl;
		  
        delete [] aborts;
        delete [] dones;
		  
        fclose( outfile );
        system( "PAUSE" );
		  
      }
    }
    else{
      cout << endl << "Command does not exist!\n" << endl;	
	}

    cout << "**** Simulate FIFO Queues by SQF *****" << endl;
    cout << "* 0. Quit                            *" << endl;
    cout << "* 1. Sort a file                     *" << endl;
    cout << "* 2. Simulate one FIFO queue         *" << endl;
    cout << "**************************************" << endl;
    cout << "Input a command(0, 1, 2):";
    
	cin >> command;
	
    delete [] arrays;
    delete [] aborts;
    delete [] dones;
  }
  return 0;
  
}

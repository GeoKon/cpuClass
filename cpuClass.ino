#include <ESP8266WiFi.h>
#include "cpuClass.h" 	// this includes Arduino.h
#define TEST1

#ifdef TEST1
//COUT print

void setup()
{
    cpu.init();
    PF( "[%d] Heap now %ld (max=%ld)\r\n", __LINE__, cpu.heapUsedNow(), cpu.heapUsedMax() );
    for(;;)
    {
        Buf s(100);
        cpu.prompt( "Press something: ", s.pntr, 80 );
        PF( "[%d] Heap now %d (max=%d)\r\n", __LINE__, cpu.heapUsedNow(), cpu.heapUsedMax() );
        if( *s.pntr == 'X' )
            break;
    }
    PF( "[%d] Heap now %ld (max=%ld)\r\n", __LINE__, cpu.heapUsedNow(), cpu.heapUsedMax() );
    //s.free();
    //PF( "[%d] Heap now %ld (max=%ld)\r\n", __LINE__, cpu.heapUsedNow(), cpu.heapUsedMax() );
    
//    print|  "you entered:" | s |"";
//    print|  "this loop:" | 10 | "variable:" | 2.34 |"";
//    print| "Multiple" | "words" | "testing" |"";
//    print|  10 | 2.34 | 30 | "";
//    print| "value 1:" | 10 |", Value2:"| 20 | ", Value3:"| 20.34 | "";

    PR("Press button to see incrementing counter");
}

static int count=0;
void loop()
{
    if( cpu.buttonPressed() )
        PF( "Count = %d\r\n", count++ );
    if( count > 10 )
        cpu.die("happy!");
    yield();
}
#endif

#ifdef TEST3
char buf[80];
int loopmax=10;

void setup()
{
  cpu.init();
  
//  cpu.prompt("Enter number of loops before assert: ", buf, sizeof(buf) );
//  loopmax = atoi( buf );

  loopmax = atoi( cpu.prompt("Enter number of loops before assert: " ));
  
  cpu.print("You entered %d. Starting Main Loop", loopmax );
  cpu.heapPrint("Heap in #1");
  char *test=new char[1000];
  cpu.heapPrint("Heap in #2");
}

int i=0;

void loop()
{
  cpu.led( BLINK, 2 );
  cpu.print("count = %d", i++ );
  PN( "Same as before = %d", i );
  
  cpu.heapUpdate();
  if( cpu.button() )
  {
    char *test=new char[100];
    cpu.print("Pressed");
    cpu.heapPrint("Heap in #3");
  }
  ASSERT( i<loopmax );  
  delay(2000);
}
#endif

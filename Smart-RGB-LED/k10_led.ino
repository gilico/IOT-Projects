#define GreenPin D3
#define RedPin D4
#define BluePin D2
#define LED_NUM 3

int ledColors[LED_NUM] = {RedPin, GreenPin ,BluePin };

void ledSetup() {
  for (int i = 0; i < LED_NUM; i++) {
  pinMode(ledColors[i], OUTPUT);
  }
}

// This method recieve's the hexstr from the server's tab
// takes each two hex value from the string and send it to convert to inteteger
// finally the method will send to each pin of the RGB LED a value from 0-255
void HexToLedRGB(String hexStr){
  int idx = 0;
  
  // start the loop from 1 to avoid the '#' of the hex string
  for(int i = 1;i < hexStr.length(); i+=2){
    
    // use substring to get the specific hex of the rgb
    String temp = hexStr.substring(i,i+2);  
    
    // write to the pin at index idx with the value that will return from 'hstol' method  
    analogWrite(ledColors[idx], hstol(temp));
    idx++;
  }
}

// converter method from 'hex-string' to 'long' and then cast it to return 'int'
int hstol(String hex){
  
  // asign the length of hex to avoid repeating it
  int len = hex.length()+1;
  
  // set a new char array
  char c[len];
  
  // implement the string to the c array
  hex.toCharArray(c, len);
  
  // FIRST ARGUMENT - c -  will use as the string to be converted
  // SECOND ARGUMENT - NULL - indicate where to stop at the string
  // THIRD ARGUMENT - 16 - used as the radix of the number
  return (int)strtol(c, NULL, 16); // return the decimal value of two combined chars as hex 
}

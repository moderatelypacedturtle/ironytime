// Array Task 1

void setup() {
  Serial.begin(9600);

  // Creat an array of type int and size 10:
  int arr[10];
  // Using a while loop, fill the array with multiples of 3 between 3 and 30 (inclusive):
                // Remember the syntax?
                // while (condition) {
                //       code...
                // }
  int i = 1;
  int k = 0;
  while (i <=30) {
    if (i%3 == 0) {
      arr[k] = i;
      k++;
    }
    i++;
  }



  // Rewrite the code above with a for loop:
                // Remember the syntax?
                // for (initialization; condition; update variable) {
                //       code...
                // 
  k = 0;
  for (int i =1; i <=30; i++) {
    if (i%3 == 0) {
      arr[k] = i;
      k++;
    }
  }



  // Write a loop that will go through the array 
  //     and print any values that are a multiple of 9:
                // Hint: Use the % (modulus) operator.
                
  int num;
  for (int i = 0; i < 30; i++) {
    num = arr[i];
    if (num % 9 == 0) {
      Serial.println(num);
      num = 0;
    }
  }
}


void loop() {
  // put your main code here, to run repeatedly:

}

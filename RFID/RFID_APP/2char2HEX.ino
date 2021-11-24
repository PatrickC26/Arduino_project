int C2I(char a){
  int b = String(a).toInt();
  int f;
  if (b == 0){
    int c = a;
    if (c != 48){
      switch (a){
        case 'A' : 
          f = 10;
        break;
        case 'B' : 
          f = 11;
        break;
        case 'C' : 
          f = 12;
        break;
        case 'D' : 
          f = 13;
        break;
        case 'E' : 
          f = 14;
        break;
        case 'F' : 
          f = 15;
        break;
        case 'a' : 
          f = 10;
        break;
        case 'b' : 
          f = 11;
        break;
        case 'c' : 
          f = 12;
        break;
        case 'd' : 
          f = 13;
        break;
        case 'e' : 
          f = 14;
        break;
        case 'f' : 
          f = 15;
        break;
      }
    }
    else  f = b;
  }
  else  f = b ;
  return f;
}

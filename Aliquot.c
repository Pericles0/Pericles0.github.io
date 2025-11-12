#include <stdio.h>

//PowerFunction : P(a,b) = a^b
unsigned long long P(unsigned long long a ,unsigned long long b) {

if(b == 0 && a != 0) {return 1;}
if(a == 0 && b !=0) {return 0;}


unsigned long long p = 1;
while(0<b){
    if(b % 2 == 1){p *= a;}
    b /= 2;
    a *= a;
}
return p;
}

/*SigmaFunction : σ(num) = SigmaF(num) - Δίνει το άθροισμα των διαίρετων ένος αριθμού num.
Αυτή τη συνάρτηση μόνη της παθαίνει υπερχείλιση εύκολα για αυτο την χρησιμοποίουμε ποιό μετά
στον ορισμό της συνάρτησης Aliquotf()  */
unsigned long long SigmaF(unsigned long long num){

unsigned long long factor,tmp,product=1;/*Ορίζω factor ως ο τρέχον πιθανός παράγοντας του num, tmp ως το τρέχον ποιλίκο της καθέ διαίρεσης 
του num με τους factors, product γιά το γινόμενο των όρων  ( P(factor,exp+1) - 1 )/(factor - 1)*/      

  tmp = num; //ο tmp θα είναι το ποίλικο κάθε διαίρεσης με τους factors.
  factor = 2;	//το 1 είναι παράγοντας κάθε αριθμού, για αυτο αρχίζουμε απο το 2
   
  while (factor * factor <= tmp) {          /* Όταν το υπόλοιπο της διαίρεσης των παραγόντων γίνει μικρότερο απο τον τρέχον
    factor*factor δεν υπάρχουν αλλοι παράγοντες να ψάξουμε δίοτι δεν υπάρχει μικρότερος παράγοντας απο το τρέχον factor στο tmp,
    εφόσον τους έχουμε ελένξει όλους μεχρι το factor. Ετσι ο μικρότερος συνδιασμός factor που θα μπορούσε να παραγοντοποίηθει
    το tmp ειναι factor*factor, το οποιο ειναι μεγαλύτερο του tmp, άρα δεν παραγοντοποιείτε αλλο.*/
	    
unsigned long long exp = 0; /*Αρχικά κάθε πιθανός παράγοντας θα είναι στην μηδενική δύναμη*/
	   while (tmp % factor == 0) { 
        exp++;  //αυξάνουμε την δύναμη του τρέχον παράγοντα εφόσον είναι παράγοντας του num.                     
	    tmp /= factor;
	    }

    unsigned long long OverflFactor = P(factor,exp + 1); //Ορίζω OverflFactor ως ο τρέχον factor στην δύναμη του +1 και ελέγχω αν ξεπερνά το όριο 10^15.
    if(OverflFactor > 1000000000000000){
                    
        return 0; //then we check with a if statement if its equal to -1 to return 1 in main
    }



    if(exp > 0){
    product *= ( OverflFactor - 1 )/(factor - 1); /*Διάβαστε το README για την απόδειξη αυτού του τύπου, ο οποίος για εναν δεδομένο αριθμό υπολόγιζει το αθροίσμα των διαιρετών του με τη βοήθεια των πρώτων παράγοντων του. */ 
    }      

        if (factor == 2) {
	    factor = 3;	
        }
	  else if (factor % 6 == 1) { //Αυτά τα else if , else αποτελούν τους factors που δεν είναι πολλαπλάσια του 2 και 3.
	factor += 4;	
	    }
	   else {
	    factor += 2;			 
        }
        }
 if (tmp != 1) {	 //Αν το tmp δεν ειναι 1,τότε το tmp ειναι prime factor του num, πρέπει να το συμπεριλάβουμε στο γινόμενο
product *= ( tmp*tmp - 1 )/(tmp - 1);
    }
return product;
}

//Η συνάρτηση Aliquotf για έναν δεδομένο αριθμό num επιστρέφει τον επομενό ορό της ακολουθείας aliquot.
unsigned long long Aliquotf(unsigned long long num){

if(num==0){return 0;}

unsigned long long factor,tmp,product=1;   
tmp = num; 
factor = 2;	

  while (factor * factor <= tmp) {          
    unsigned long long exp = 0;   
    
    while (tmp % factor == 0) {
	    exp++;
        tmp /= factor;
	    }

        if(exp > 0){
            unsigned long long SigmaF_P_factor = SigmaF(P(factor ,exp)); //Η συνάρτηση σ(x) είναι πολλαπλασιαστική για δύο αριθμούς α,β αν gcd(α,β) = 1
            if(SigmaF_P_factor == 0){ return 0;} //Θυμόμαστε πως η Sigmaf επιστρέφει -1 οταν περνά το όριο.   
            product *= SigmaF_P_factor; //επείδη η σ(x) είναι πολλαπλασιαστική εδώ, ισχύει σ(α,β...,n) = σ(α)*σ(β)*...*σ(n).
            if(product > 1000000000000000){return 0;}
        }

        if (factor == 2) {
	    factor = 3;	
        }
	  else if (factor % 6 == 1) { 
	factor += 4;	
	    }
	   else {
	    factor += 2;			 
        }
        }
 if (tmp != 1) { //Αν tmp δεν ειναι 1 τοτε είναι πρώτος, και η σ(πρώτου) = πρώτος + 1	 
product *= (tmp + 1);
    }
return (product - num);
}


int main() {
    /*ορίζω τις μεταβλητές num για τον τρέχον όρο στην ακολούθειας, Lmax για τo μέγιστο μήκος της ακολουθείας, 
    L το μήκος της ακολουθείας και prf για την προτιμηση f η l*/
    
    unsigned long long num , Lmax , L;
    char prf;
    //εισοδος αριθμου για την έναρξη της ακολουθείας, ορίζω scannum για να τσεκάρω αν δώθηκε σωστή είδοσος με τη βοηθεία της if
    printf("Please give the number to start the aliquot sequence from:");
    int scannum = scanf("%llu", &num);
    
    if(scannum != 1|| num > 1000000000000000){printf("Invalid Input for the Number, program is expecting positive integer smaller than 10^15.\n");
    return 1; }

    //εισοδος αριθμου για τo μέγιστο μήκος της ακολουθείας, ορίζω scanLmax για να τσεκάρω αν δώθηκε σωστή είδοσος με τη βοηθεία της if
    printf("Provide the max aliquot length to look for (0 for unlimited):");
    int scanLmax = scanf("%llu",&Lmax);
    if(scanLmax != 1){printf("Invalid Input for the max aliquot length, program is expecting positive integer.\n");
    
    return 1; }

    //εισοδος προτιμήσης, ορίζω scanprf για να τσεκάρω αν δώθηκε σωστή είδοσος με τη βοηθεία της if
    printf("Do you want to print the full sequence ('f') or just the length ('l')?");
    int scanprf = scanf(" %c", &prf);
    if(scanprf != 1 || (prf != 'f' && prf != 'l')){printf("Invalid Input for the max aliquot length, program is expecting 'l' or 'f'.\n");
    
    return 1; }
    
    //Τυπώνουμε τον πρώτο αριθμό της ακολουθείας, διοτί οι επόμενοι όροι τυπώνονται μετά τον υπολογισμό τους.   
    if(prf == 'f') {printf("%llu\n", num);}

    
    
    
    for(L=1 ; Lmax==0 || L <= Lmax ; L++){
        if(num == 1){ //Χρισημοποιούμε την τιμή 0 για να δηλώσουμε error στις συναρτησείς τυπου unsigned long long, για αυτό πρέπει οταν num = 1 να επιστέψουμε την τιμή εμείς και όχι στις συναρτήσεις.
            if(prf == 'f') {printf("%d\n",0);}
            break;
        }
        if(num > 1000000000000000){printf("Number exceeds maximum supported integer (1000000000000000). Stopping."); //Η aliquotf() που ορίσαμε επιστρέφει 0 όταν κατά τον υπολογισμό περνά το όριο 10^15. 
        return 1;
        }

        num  = Aliquotf(num); //Υπολογίζουμε τον επόμενο όρο της ακολουθείας aliquot.
        if(num == 0){printf("Number exceeds maximum supported integer (1000000000000000). Stopping."); //Η aliquotf() που ορίσαμε επιστρέφει 0 όταν κατά τον υπολογισμό περνά το όριο 10^15. 
       return 1;
        }

        if(prf == 'f') {printf("%llu\n", num);} 
        
        
    }
        

 
 if(prf == 'l'){printf("Length of aliquot sequence: %llu\n",L);}
    

return 0;
}

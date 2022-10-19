#include <iostream>
#include <fstream>
#include <string>
#include <climits>
using namespace std;

//Dit is een programma voor het decoderen en encoderen met
//behulp van een pincode. Daarnaast worden getallen in de
//file herkent en het lychrel getal ervan vertoond. In het
//geval dat de gebruiken zijn pincode is vergeten, moet de
//code de pincode vinden door de encodeerde file te brute
//forcen en te checken of 'the' het vaakst voorkomt.
//
//De gebruiker wordt gevraagd of hij wilt decoderen of coderen
//en moet of 'c' of 'd'. Vervolgens wordt gevraagd naar het
//pad. Vul hier de naam van de file met de extensie(gebruik het
//liefst een txt.). Als de invoer of uitvoer in een ander map
//zit dan het programma, verwijs de mappen en de file(bijvoorbeeld
//map1/map2/file.txt). Vervolgens wordt bij zowel coderen als
//decoderen een pincode gevraagd. Bij coderen voer een zelf-
//gekozen pincode. Als je bij decodern wilt brute forcen,gebruik
//-1 als pincode.
//
//datum:		17 Oktober 2022
//onderwijsinrichting:	Universiteit Leiden
//namen:		Sami Fesenko & Jimmy Chao
//studentennummers:	s3587584 & s3496116
//gebruikte editors:	gedit, notepad++, code::blocks
//gebruikte compiler:	g++, g++ in WSL, code::blocks
//betekenissen van returns:
//
//0: programma eindigt zoals het hoort" << endl
//1: programma eindigt geforceerd door een fout

void infoblok(){
	cout << "programmeeropgave 2: pincode" << endl;
	cout << "Dit is een programma voor het decoderen en encoderen met" <<endl;
	cout << "behulp van een pincode. Daarnaast worden getallen in de" <<endl;
	cout << "file herkent en het lychrel getal ervan vertoond. In het" <<endl;
	cout << "geval dat de gebruiken zijn pincode is vergeten, moet de" <<endl;
	cout << "code de pincode vinden door de encodeerde file te brute" <<endl;
	cout << "forcen en te checken of 'the' het vaakst voorkomt." <<endl <<endl;
	cout << "datum:			17 Oktober 2022" <<endl;
	cout << "onderwijsinrichting:	Universiteit Leiden" <<endl;
	cout << "namen:			Sami Fesenko & Jimmy Chao" <<endl;
	cout << "studentennummers:	s3587584 & s3496116" <<endl;
}

int vraagCD (bool & C1D0) {  //vraagt of het gaat om coderen of decoderen,
	char antwoord;			 //geeft boolean C1D0 terug.
	cout << "gaat het om coderen of decoderen? [C/D]" << endl;
	cout << "Antwoord met C of D" << endl;
	cin >> antwoord;
	if (antwoord == 'C' || antwoord == 'c') {
		C1D0 = true;
		return C1D0;
	} else if (antwoord == 'D' || antwoord == 'd'){
		C1D0 = false;
		return C1D0;
	} else {
		cout << "bruh momento" << endl;
		return 1;
	}
}

void wissel (int & a, int & b, int & c, int & d) {  //wisselt individuele 
	int hulp = a;									//getallen
	a = b;
	b = c;
	c = d;
	d = hulp;
}

void setpin(int & a, int & b, int & c, int & d, int & pin) { 
	a = (pin / 1000) % 10; 				//verdeelt getal met 4 cijfers 
	b = (pin / 100)  % 10;				//in 4 verschillende ints
	c = (pin / 10) % 10;							
	d = pin % 10;
}

int readGetal(char & prevkar, char & kar, int & som) { 
	int getal = 0;					//functie die een getal leest uit een
	if ('0' <= kar && kar <= '9') { //file en omzet in een int.
		som = 10 * som + (kar - '0');//zet alle karakters die cijfers zijn
	}								//om in een int.
	
	if ('0' <= prevkar && prevkar <= '9') { //als vorig karakter een cijfer
		if('0' > kar || kar > '9') {	//is en huidig karakter niet 
				getal = som;			//een cijfer is, geef getal.
				som = 0;
			}
	}
	return getal;
}

int reverseGetal(int getalplus) { //functie dat een getal omgekeerd draait.
	int getalrev = 0;
	while (getalplus != 0) {  //vermenigvuldigt vorig getal + mod10 van
		getalrev = 10 * getalrev + (getalplus % 10); //getal, vervolgens
		getalplus = getalplus / 10;  //wordt het getal gedeeld door 10.
	}
	return getalrev;
}

int checklychrel(int checkgetal) { 		//functie voor het berekenen van 
	int getalrev = reverseGetal(checkgetal);//een potentieel lychrel nummer
	int getalplus;
	int iteratie = 0;
	while ((reverseGetal(checkgetal) != checkgetal) && //loopt totdat 
			(checkgetal < INT_MAX - getalrev)) { //palindroom of overflowt
		getalrev = reverseGetal(checkgetal);  
		getalplus = getalrev + checkgetal;
		checkgetal = getalplus;  //resultaat wordt opnieuw gecheckt
		iteratie++;
	}
	if((reverseGetal(checkgetal) != checkgetal) && //geen palindroom en 
		(checkgetal > INT_MAX - getalrev)) {  //overflowt
		iteratie++;
		cout << "potentieel Lychrel-getal." << endl;
		cout << "Iteraties tot INT_MAX: " << iteratie << endl << endl;
	} else {
		cout << "iteraties tot palindroom: " << iteratie << endl << endl;
	}
	return iteratie; //geeft aantal iteraties terug
}

int codeer(int kar,int & pin) { //een beetje redundant, maar toch in
	int karencint = kar + pin;	//functie gezet, neem de int van kar + de 
	if (karencint > 126) {		// cijfer van pincode.
		karencint = (95+karencint) % 95;
	}
	return karencint;
}

int decodeer(int kar,int & pin) {//ook redundant
	int karencint = kar - pin;
	if (karencint < 32) {
		karencint = karencint + 95;
	}
	return karencint;
}

int ReadWrite (string & invoer, string & uitvoer, int pin,
				bool & c1d0, bool & brutepin) { //functie die file leest en
	ifstream input(invoer);
	ofstream output;	//schrijft, plus de (de)codeer
	if (!brutepin) {	//opent pas uitvoer als niet aan het bruteforcen.
		output.open(uitvoer);		//specificaties
	}
	int nLinefeed = 0;	//aantal linefeeds.
	int nKar = 0;		//aantal karakters.
	int nThe = 0;		//aantal the's.
	
	int a,b,c,d;		//individuele ints voor pin.
	setpin(a,b,c,d,pin);  //zet de pin uit vraagpin.
	
	char prevprevkar, prevkar, kar; // huidige kar & vorige 2 kar's.
	kar = input.get();				// leest de invoerfile.
	int som = 0, getal;				// ints voor het lezen van getal.
	bool waitOne = false;			// boolean die eerste kar bij nieuwe 
									//pin overslaat.
	int decgetal;
	while (!input.eof()) {	// kar reader loop
		if (waitOne) { //pin wordt pas gereset bij volgende kar
			setpin(a,b,c,d,pin); //activeert alleen bij nieuw getal.
			waitOne = false; 
		}
		
		if (c1d0) { //alleen bij coderen.
			getal = readGetal(prevkar,kar,som); //leest getal.
			
			prevprevkar = prevkar; //neemt de vorige twee karakters.
			prevkar = kar; 
	
			if ( getal > 0 && getal < 10000) { //veranderd pin naar getal 
				pin = getal;				   //in input tussen 0-9999.
				waitOne = true;				
			} 
		
			if (getal != 0) {	//lychrel getal controle functie.
				cout << "Gedetecteerd getal: " << getal << endl;
				checklychrel(getal);
			}
		}

//coderen en decoderen
		if (kar != '\n' && kar != '\t' && kar != '\r') {  
			if (c1d0) {	//codeert
				kar = char(codeer(int(kar),a));
			} else { //decodeert
				kar = char(decodeer(int(kar),a));
			}
			wissel(a,b,c,d); //wisselt de pincode
		} else {
			setpin(a,b,c,d,pin); //reset de pincode
		}
		
		if (!c1d0) { //als het decoderen is
			if ((prevprevkar == 't' || prevprevkar == 'T') && 
			(prevkar == 'h' || prevkar == 'H') && 
			(kar == 'e' || kar == 'E')) {
				nThe++;
			}	//telt aantal keer 'the'
			
			decgetal = readGetal(prevkar,kar,som); //leest getal in invoer
						
			prevprevkar = prevkar;
			prevkar = kar;
			
			if (decgetal > 0 && decgetal < 10000) { //verandert pin naar 
				pin = decgetal;						//getal tussen 0-9999.
				waitOne = true;
			}
		}

		if (!brutepin) {			//als bruteforce overslaan.
			if (kar == '\n') {		//leest aantal linefeed.
				nLinefeed++;
			}
			nKar++;					//telt aantal karakters op.
			output.put(kar); 		//schrijft naar output.
			}
		
			kar = input.get();		//neemt volgende karakter.
		}	//einde kar reader loop.
		
	if (!brutepin) {	//als bruteforce overslaan.
		cout << "Aantal regels: " << nLinefeed << endl; 
		cout << "Aantal karakters: " << nKar << endl;
		output.close(); //sluit output.
}
	input.close(); //sluit input.
	return nThe; //geeft aantal the's in main().
}


int main () {
	infoblok();	
	bool C1D0 = vraagCD(C1D0); //geeft aan of het coderen of decoderen is
	
	string iFile;  //originele file
	string oFile;  //doelfile
	cout << "Geef het pad van het oorspronkelijke bestand:" << endl;
	cin >> iFile;
	cout << endl << "Geef het pad voor het nieuwe bestand:" << endl << endl;
	cin >> oFile;
		
	int pin;
	cout << "Wat is de pincode?" << endl;
	cout << "Geef een getal tussen 0-9999" << endl;
	cin >> pin;
	if (C1D0) {
		if (pin < 0 || pin > 9999) { 		//geeft error als niet tussen 
			cout << "bruh momento" << endl;	//0-9999.
			return 1;
		}
	} else {
		if (pin < -1 || pin > 9999) { 		//geeft error als niet tussen
		cout << "bruh momento" << endl;		//-1-9999
		return 1;
		}
	}
	
	int leeftijd;
	string geboorteplaats;
	int BSN;
	cout << "wat is uw leeftijd?" << endl;
	cin >> leeftijd;
	cout << endl << "wat is uw geboorteplaats?" << endl;
	cin >> geboorteplaats;
	cout << endl << "wat is uw BSN nummer?" << endl;
	cin >> BSN;
	cout << endl << endl;
	
	int nThe=0,mostThe=0,secretpin;		//ints voor aantalthes en pin.
	bool brutepin = false;				//geen bruteforce by default.
	if (pin == -1) {					
		for (int i = 0; i < 10000; i++) {
			brutepin = true;			//wel bruteforcen.
			pin++;						//telt het te checken pin op.
			cout << pin << endl;
			nThe = ReadWrite(iFile,oFile,pin,C1D0,brutepin);
			if (mostThe < nThe) {	//slaat pin en meeste the's op.
				mostThe = nThe;		//slaat aantal the's uit ReadWrite op.
				secretpin = pin;	//slaat pin met meeste the's op.
			}
		}
		brutepin = false;	//einde van loop, dus wel naar output schrijven
		ReadWrite(iFile,oFile,secretpin,C1D0,brutepin); //met secretpin
		cout << "geheime pincode: " << secretpin << endl;
		cout << "Aantal 'The's' in gedecodeerd bestand: " << mostThe << endl;
	} else { 
	ReadWrite(iFile,oFile,pin,C1D0,brutepin); //als pin != -1, dan 1x runnen
	}
	return 0; //einde programma naar behoren
}
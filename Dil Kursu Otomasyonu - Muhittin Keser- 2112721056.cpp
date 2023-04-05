
#include <iostream>
using namespace std;
#include <fstream>
#include <string.h>
#include <windows.h>

struct diller{

	char dilAdiveSeviye[20] ;
	int dilSaatBasiUcret ;
	int sinifDoluluk = 0;

};

struct ogrenciler {

	char ad[40] ;
	char soyad[20] ;
	char dil[20] ;
	char cinsiyet ;
	int egitimSaati ; // sözleşmeye göre kaç saat eğitim göreceği .
	int toplamUcret ;  // sözleşmeye göre yıl sonu toplam ücret



};

struct ogretmenler {

	char ad[40] ;
	char soyad[20] ;
	char dil[20] ;
	char cinsiyet ;
	int egitimSaati ; // sözleşmeye göre kaç saat eğitim vereceği .
	int toplamUcret ;  // sözleşmeye göre yıl sonu alacağı ücret .


};

diller dil ;
ogretmenler ogretmen ;
ogrenciler ogrenci ;


void dilEkle(){

	cout << "dilin adını ve seviyesini girin : " ; cin >> dil.dilAdiveSeviye ;
	cout << "saat başı ücretini girin : " ; cin >> dil.dilSaatBasiUcret ;

	dil.sinifDoluluk = 0 ;


	ofstream dilBilgileri("dilbilgileri.txt" , ios::app);
	dilBilgileri.write((char*)&dil , sizeof(dil));


}

void ogretmenEkle(){

	cout <<"öğretman adı :" ;
	cin >> ogretmen.ad ;
	cout << "öğretmen soyadı : ";
	cin >> ogretmen.soyad ;
	cout << "öğretmenin vereceği dil :" ;
	cin >> ogretmen.dil ;

	bool durum = true ;
	// öğretmene atanan dil önceden eklenmişmi kontrol edelim :
	// ilk başta dilbilgileri.txt dosyasının içindeki tüm nesneleri okumalıyım klasik algoritmayla .
	ifstream dilBilgileriOku("dilbilgileri.txt");
	dilBilgileriOku.seekg(0,ios::end);
	int kacDil = dilBilgileriOku.tellg() / sizeof(dil) ;

	while(true){
	for(int i = 0 ; i<kacDil ; i++){

		dilBilgileriOku.seekg(i*sizeof(dil) , ios::beg) ;
		dilBilgileriOku.read((char*)&dil , sizeof(dil));
		if(strcmp(ogretmen.dil , dil.dilAdiveSeviye) == 0  ){
				durum = false ;
			break ;
		}


	}


	if(durum){
		cout << "girdiğiniz dil kayıtlı değil tekrar deneyin" << endl ;
		cin >> ogretmen.dil ;


	}
	else{
		cout << "girdiğiniz dil kayıtlı. şimdi cinsiyet ve öğretmenin vereceği eğitim saatini belirtin" << endl ;
		cout << "öğretmenin cinsiyeti:" ;
		cin >> ogretmen.cinsiyet ;
		cout << "öğretmenin toplam vereceği eğitim saati : " ;
		cin >> ogretmen.egitimSaati ;
      break ;
	}



	}


	ofstream ogretmenBilgileri("ogretmenbilgileri.txt" , ios::app);
	ogretmenBilgileri.write((char*)&ogretmen , sizeof(ogretmen));

}

void ogrenciEkle(){
	cout << "öğrenci adı : " ; cin >> ogrenci.ad  ;
	cout << "öğrenci soyadı : "; cin >> ogrenci.soyad ;
	cout << "öğrencinin eğitim göreceği dil : " ; cin >> ogrenci.dil ;


	//////
	bool durum = false ;

		ifstream dilBilgileriOku("dilbilgileri.txt");
		dilBilgileriOku.seekg(0,ios::end);
		int kacDil = dilBilgileriOku.tellg() / sizeof(dil) ;

		diller yenidiller ;
		for(int i = 0 ; i<kacDil ; i++){

			dilBilgileriOku.seekg(i*sizeof(dil) , ios::beg) ;
			dilBilgileriOku.read((char*)&dil , sizeof(dil));
			if(strcmp(ogrenci.dil , dil.dilAdiveSeviye) == 0  ){
					cout << "böyle bir dil var , belirttiğiniz dil sınıfına 1 kişi ekleniyor..." << endl ;
					dil.sinifDoluluk++ ; // dilin sınıf doluluğunu arttırdıktan sonra dilbilgileri.txt te o veriyi güncellememiz ve buradan yazdırmamız gerekiyor .
		durum = true ;

			}

						ofstream yeniDilBilgileri("yenidilbilgileri.txt" , ios::app) ;

						yenidiller = dil ;
						yeniDilBilgileri.write((char*)&yenidiller , sizeof(yenidiller));
						yeniDilBilgileri.close();






		}

		if(durum){
			dilBilgileriOku.close();  // remove ve rename işlemlerinden önce kullanılan metin belgesini close() yapmalıyız.

			remove("dilbilgileri.txt");
				rename("yenidilbilgileri.txt" ,  "dilbilgileri.txt");
				cout << "sınıfa bir kişi eklendi" << endl ;



		}
		else{
			remove("yenidilbilgileri.txt");
		}

		ifstream yeniSorgula("dilbilgileri.txt");
		yeniSorgula.seekg(0,ios::end);
		int kac= yeniSorgula.tellg() / sizeof(dil) ;

			for(int i = 0 ; i<kac ; i++){
				yeniSorgula.seekg(i*sizeof(yenidiller) , ios::beg);
				yeniSorgula.read( (char*)&yenidiller, sizeof(yenidiller) );

				if(strcmp(yenidiller.dilAdiveSeviye , ogrenci.dil ) == 0 ) {
						cout << "doluluk oranı : " << yenidiller.sinifDoluluk << endl ;
				}

			}


// en son yeni öğrenciyi metin belgesine ekleyelim .
		ofstream ogrenciBilgileri("ogrencibilgileri.txt"  , ios::binary |ios::app);
		ogrenciBilgileri.write((char*)&ogrenci,sizeof(ogrenci));
		ogrenciBilgileri.close() ;



}

void ogretmenUcretHesapla(){
	char ogretmenAdi[40] ;
	char ogrdil[40] ;
	int ucret ;
	cout <<"hangi öğretmenin yıl sonu ücretini hesaplayacaksınız ? " ; cin >> ogretmenAdi ;
	cout << "öğretmenin eğitim verdiği dili girin: " ; cin >> ogrdil ;

	ifstream ogretmenSorgula("ogretmenbilgileri.txt");
	ogretmenSorgula.seekg(0,ios::end);
	int sayac1 = ogretmenSorgula.tellg() / sizeof(ogretmen) ;
	for(int i = 0 ; i<sayac1 ; i++){
		ogretmenSorgula.seekg(i*sizeof(ogretmen) , ios::beg);
		ogretmenSorgula.read((char*)&ogretmen ,sizeof(ogretmen) );

		if(strcmp(ogretmen.ad , ogretmenAdi ) == 0){
			cout << "öğretmen bulundu. ücreti hesaplanıyor..." << endl ;

			ifstream dilbilgileriOku("dilbilgileri.txt");
			dilbilgileriOku.seekg(0,ios::end);
			int sayac2 = dilbilgileriOku.tellg()/sizeof(dil);

			for(int i = 0 ; i<sayac2 ; i++){

				dilbilgileriOku.seekg(i*sizeof(dil));
				dilbilgileriOku.read((char*)&dil , sizeof(dil));

				if(strcmp(dil.dilAdiveSeviye , ogrdil) == 0){
					cout << "öğretmenin alacağı toplam ücret : " << dil.dilSaatBasiUcret * ogretmen.egitimSaati  << endl  << endl ;
				}

			}


		}


	}

}


int main() {

	system("color 4D") ;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	setlocale(LC_ALL, "Turkish");

cout << "|-----------HOŞDELDİNİZ-------------| "  << endl << endl ;
cout << "       1)ders ekle (ön koşul)  "  << endl ;
cout << "   2)öğretmen ekle (2.ön koşul) "  << endl ;
cout << "        3)öğrenci ekle "  << endl ;
cout << "      4)öğretmen ücret hesapla "  << endl << endl ;
cout << "  ----Dil kursu Otomasyonu  v0.1----"  << endl ;
char secim ;
cin >> secim ;

	switch(secim){

	case '1' :

		dilEkle();

	break ;

	case '2' :

		ogretmenEkle();

break ;

	case '3' :

		ogrenciEkle();

			break ;


	case '4' :

		ogretmenUcretHesapla();

	}

main();
	return 0;
}

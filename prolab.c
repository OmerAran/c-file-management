#include <stdio.h>
#include <stdlib.h>//dinamik bellek yönetimi yapabilmek yani malloc gibi fonks. dahil etmek için eklenen kütüphane
//#include <ctype.h>

int sabit = 50 ; // 50 kişilik veri verememiz istendiği için sabit tanımlamada bir olumsuzluk görmedik

struct kayit{ // struct tanımlıyoruz, istediğimiz özellikleri (ogr no, ders kodu ve sınav puan gibi) tanımlıyoruz.
    int ogrno;
    int derskodu;
    int puan;
    int derskodu2 ;
    int puan2 ;

};

struct kayit *sinif; // struct tipinde bir pointer tanımlıyoruz.

FILE *indexFile; // index dosyası için FILE pointerı tanımlıyoruz
FILE *binFile ;  // binary dosyası için FILE pointerı tanımlıyoruz

void indexDosyasiOlustur(){  //fonksiyon

    binFile=fopen("/Users/omeraran/desktop/okul.bin", "wb"); // fopen ile binary dosyayı yazma modunda açıyoruz.

    for (int i = 0; i<sabit; i++) { //bu döngü fprintf fonksiyonunu kullanarak binary dosyasına yazmaya yarıyor.
        fprintf(binFile, "%d \t%d \t %d \t  %d \t  %d\n",sinif[i].ogrno,sinif[i].derskodu,sinif[i].puan, sinif[i].derskodu2,sinif[i].puan2);

    }
    fclose(binFile); //dosyayı kapatıyoruz.

    indexFile = fopen("/Users/omeraran/desktop/veri.txt","w"); // indeks dosyasını yazma modunda açıyoruz
    binFile = fopen("/Users/omeraran/desktop/okul.bin","rb"); // tekrar binary dosyayı açıyoruz ama bu sefer okuma modunda.


    fprintf(indexFile,"no \t ders1\tNot1\tders2\t not2\n-------------------------------------------------- \n");

    if (indexFile==NULL) {
        printf("////////////////// Dosya olusturalamadi //////////////////");
        //hata ayıklamak amacıyla dosya oluşması gerçekleşmezse kullanıcıya bilgi vermek aynı zamanda programın çalışmaya devam etmeye sağlamak.
    }
    else{
        while(!feof(binFile)){ // eger dosya oluştuysa  while döngüsüyle  tek tek binary dosyadan index dosyasına yazma işlemi yapılıyor.
            fprintf(indexFile,"%c",fgetc(binFile));
        }
    }
    fclose(indexFile); // dosyalar kapatılıyor...
    fclose(binFile);
}

void siralama(){
    /*
     sıralama fonksiyonu yazdık,birden fazla kez kullanacağımız için hem maliyetten kaçınmak hem de pratik olması için.
    */
    int i,j,gecici;

    for(i=0;i<sabit;i++){
        for(j=1;j<sabit-i;j++){
            if(sinif[j-1].ogrno>sinif[j].ogrno){         // Kendi sorting Algoritmamızı oluşturduk..BUBLE SORT SANIRIM
                gecici=sinif[j].ogrno;
                sinif[j].ogrno=sinif[j-1].ogrno;
                sinif[j-1].ogrno=gecici;

                gecici=sinif[j].derskodu;
                sinif[j].derskodu=sinif[j-1].derskodu;
                sinif[j-1].derskodu=gecici;

                gecici=sinif[j].puan;
                sinif[j].puan=sinif[j-1].puan;
                sinif[j-1].puan=gecici;

                gecici=sinif[j].derskodu2;
                sinif[j].derskodu2=sinif[j-1].derskodu2;
                sinif[j-1].derskodu2=gecici;

                gecici=sinif[j].puan2;
                sinif[j].puan2=sinif[j-1].puan2;
                sinif[j-1].puan2=gecici;

            }
        }
    }

    indexDosyasiOlustur();
}

int Binarysearch(int aranan){
    /* sorting fonksiyonu gibi pratik olması amacıyla sıralı arama yaparken de
     maliyet anlamında kazancımız olması amacıyla fonksiyon olarak ayırdık.
    */
    siralama();
    int buyuk=sabit,kucuk=0;

    while(kucuk<=buyuk){

        int orta=(buyuk+kucuk)/2;

        if(aranan == sinif[orta].ogrno){
            return orta;
        }
        else if(aranan<sinif[orta].ogrno){
            buyuk=orta-1;
        }
        else{
            kucuk = orta+1;
        }

    }
    return -1;
}


void indeksDosyasiniGoster(){
    indexFile = fopen("/Users/omeraran/desktop/veri.txt","r");// okuma modunda txt dosyasını açıyoruz.

    if (indexFile==NULL) {
        printf("Istenen Dosya Yok."); // bulunmazsa hata verip ,çalışmaya devam edicek.
    }
    else{
        while(!feof(indexFile)){   //binary dosyadan index dosyasına verileri yazıyoruz.
        putchar(fgetc(indexFile));
        }
    }


    fclose(indexFile);

}

void kayitGuncelle(int i ){

    int gunNo=Binarysearch(i);
    printf("%d numaralý ogrencinin ; \nnotlarý: %d\t %d\nHangi dersi güncelleyecekseniz o dersin kodunu yazýnýz : ",sinif[gunNo].ogrno,sinif[gunNo].puan,sinif[gunNo].puan2);
    int hangiDers ,yeniPuan;;
    scanf("%d",&hangiDers);
    if (hangiDers == sinif[gunNo].derskodu) {
        printf("Yeni puani giriniz : ") ;
        scanf("%d",&yeniPuan);
        sinif[gunNo].puan=yeniPuan;
        printf("Yeni notu: %d olarak güncellendi.",sinif[gunNo].puan);
    }
    else if (hangiDers == sinif[gunNo].derskodu2){
        printf("Yeni puani giriniz : ") ;
        scanf("%d",&yeniPuan);
        sinif[gunNo].puan2=yeniPuan;
        printf("Yeni notu: %d olarak guncellendi.",sinif[gunNo].puan2);
    }
    else{
        printf("////////////////// Bu ogrenci girmis oldugunuz dersi almiyor.//////////////////");
    }

    indexDosyasiOlustur();

}

void kayitEkle(){

    int yeniOgrNo ;
    printf("\n////////////////// Yeni ogrenci eklemeye hos geldiniz //////////////////\nYeni ogrenci no: ");
    scanf("%d", &yeniOgrNo);

    if (Binarysearch(yeniOgrNo)==-1) {
        // eğer binarysearch'de bu numara bulunmazsa -1 döner ve gerçekleşirse işleme devam edebiliriz.
        sinif[sabit].ogrno =yeniOgrNo ;
        printf("Ders kodunu giriniz: ");
        scanf("%d",&sinif[sabit].derskodu);
        printf("Puanini giriniz: ");
        scanf("%d",&sinif[sabit].puan);
        // SIRA SIRA DEĞERLERİ ALIYORUZ,TEK SATIRDA ALINCA GÜZEL BİR İZLENİM VERMİYORDU KONSOL.
        printf("2.ders kodunu giriniz: ");
        scanf("%d",&sinif[sabit].derskodu2);
        printf("2.ders puanini giriniz: ");
        scanf("%d",&sinif[sabit].puan2);

        sabit++ ; // KAYIT EKLEDİĞİMİZ İÇİN SABİTİ ARTIRMALIYIZ
        siralama(); // ve yeni eklenen öğrencinin de sıralamaya katılıp küçükten büyüğe sıralanması gerek.
    }
    else{
        printf("/////////////////////// Bu numaraya sahip ogrenci bulunmaktadir..! ///////////////////////\n");
        //-1 dönmezse o numarada ogr vardır.
    }


}


void indeksDosyasiniSil(){


    int silindiMi;
    silindiMi = remove("/Users/omeraran/desktop/veri.txt");

    if(silindiMi == 0)
        printf("\n\n////////////////// Dosya basariyla silindi. //////////////////");

    else
        printf("////////////////// Dosya silinemedi! //////////////////");


}

void kayitBul(){
    printf("Bulmak istediginiz ogrencinin numarasini giriniz: ");
    int i ;
    scanf("%d",&i);
    int varMi=Binarysearch(i);
    if(varMi == -1){
        printf("////////////////// Ogrenci bulunamadi. //////////////////");
    }
    else{
        printf("////////////////// \n %d nolu ogrencinin \n birinci derskodu: %d\n birinci ders puani:%d\n ikinci derskodu: %d\n ikinci ders puani:%d \n//////////////////// \n",
               sinif[varMi].ogrno,sinif[varMi].derskodu,sinif[varMi].puan,sinif[varMi].derskodu2,sinif[varMi].puan2);
    }

}
void veriDosyasiniGoster(){
    binFile = fopen("/Users/omeraran/desktop/okul.bin", "rb");

    if (binFile==NULL) {
        printf("Veri Dosyasi Bulunamadi.");
    }
    else{
        while(!feof(binFile)){
            putchar(fgetc(binFile));
        }
    }


    fclose(binFile);
}
void kayitSil(){
    printf("Silmek istediginiz ogrencinin no: ");
    int silOgrNo;
    scanf("%d",&silOgrNo);
    int aranan=Binarysearch(silOgrNo);

     if (aranan==-1) {
        printf("Kullanici zaten yok");
    }
    else{
        for(int i =aranan ;i<sabit;i++){
            sinif[i].derskodu2=sinif[i+1].derskodu2;
            sinif[i].puan2=sinif[i+1].puan2;
            sinif[i].derskodu=sinif[i+1].derskodu;
            sinif[i].puan=sinif[i+1].puan;
            sinif[i].ogrno=sinif[i+1].ogrno;
        }
        printf("Kullanici Basariyla Silindi.\n");
        sabit--;
    }
    indexDosyasiOlustur();
}

int main()
{
    sinif = (struct kayit*)malloc(100*sizeof(struct kayit));

    for(int i= 0 ;i<sabit;i++){

        sinif[i].ogrno=200+i;
        sinif[i].derskodu=rand()%2+1;
        sinif[i].puan=rand()%50+50;
        sinif[i].derskodu2=rand()%2+3;
        sinif[i].puan2=rand()%50+50;
    }


    int islemSec;


    do {



        printf("\n1.Index Dosyasi Olustur");
        printf("\n2.Index Dosyasini Goster");
        printf("\n3.Index Dosyasini Sil");
        printf("\n4.Veri Dosyasini Goster");
        printf("\n5.Kayit Bul");
        printf("\n6.Kayit Ekle");
        printf("\n7.Kayit Guncelle");
        printf("\n8.Kayit Sil");
        printf("\n0.Cikis icin 0'a basiniz.");

        printf("\nYapmak istediginiz islemi seciniz : ");
        scanf("%d",&islemSec);

        switch (islemSec){
            case 1:
                indexDosyasiOlustur();
                break;

            case 2:
                indeksDosyasiniGoster();
                break;
            case 3:
                indeksDosyasiniSil();
                break;

            case 4:
                veriDosyasiniGoster();
                break;

            case 5:
                kayitBul();
                break;

            case 6:
                kayitEkle();
                break;

            case 7:
                printf("Ogrenci numarasini giriniz: ");
                int a;
                scanf("%d",&a);
                kayitGuncelle(a);
                break;

            case 8 :
                kayitSil();
                break;

            case 0:
                break;
            default:
                printf("Yanlis bir sayi girdiniz.Tekrar deneyiniz.");
                break;

        }


   } while (islemSec !=0);



    return 0;
}

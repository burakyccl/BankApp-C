#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    int musteriNo;
    int sifre;
    char musteriAd[30];
}musteri;

typedef struct{
    int hesapNo;
    int hesapKisi;
    float hesapBakiye;
}hesap;

typedef struct{
    int dekontHesap;
    int islemTipi;
    float miktar;
    int gun;
    int ay;
    int yil;
    int saniye;
    int dakika;
    int saat;
}dekont;

void musteriEkle(){
    FILE *fPtr;
    musteri yeniMusteri;
    int musteriTipi;

    menu2:
        printf("\n 1-Bireysel Musteri Ekle\n");
        printf(" 2-Kurumsal Musteri Ekle\n->");
        scanf("%d", &musteriTipi);

        switch(musteriTipi){
                case 1:
                    printf("\n Ad ve Soyadinizi Giriniz: ");
                    scanf(" %[^\n]s", &yeniMusteri.musteriAd);
                    if ((fPtr = fopen("bireyselMusteri.txt", "w+")) == NULL) puts("Dosya Acilamadi."); fclose(fPtr);
                    if ((fPtr = fopen("bireyselMusteri.txt", "rb+")) == NULL) puts("Dosya Acilamadi."); break;
                case 2:
                    printf("\n Kurum Adini Giriniz: ");
                    scanf(" %[^\n]s", &yeniMusteri.musteriAd);
                    if ((fPtr = fopen("kurumsalMusteri.txt", "w+")) == NULL) puts("Dosya Acilamadi."); fclose(fPtr);
                    if ((fPtr = fopen("kurumsalMusteri.txt", "rb+")) == NULL) puts("Dosya Acilamadi."); break;
                default: system("cls"); printf("\n\a\t!Hatali Giris!\t Lutfen Tekrar Giris Yapiniz.\n"); goto menu2;
        }
    system("cls");
    //MUSTERI NUMARASI VE MUSTERI SIFRESI ATAMASI
    yeniMusteri.musteriNo = (rand()%89999999)+10000000;
    yeniMusteri.sifre = (rand()%8999)+1000;
    //MUSTERI NUMARASINA GORE BILGILER DOSYAYA OZEL KONUMA KAYIT EDILIYOR
    fseek(fPtr, (yeniMusteri.musteriNo - 1) * sizeof(yeniMusteri), SEEK_SET);
    fwrite(&yeniMusteri, sizeof(yeniMusteri), 1, fPtr);
    fclose(fPtr);
    printf("\n\t\t!Kayit basarili! %c \n\n  *Lutfen Numaranizi Kayit Ediniz ve Sifrenizi Kimseyle Paylasmayiniz!",1);
    printf("\n\n\tSayin %s,\n\tMusteri Numaraniz: %d \tSifreniz: %d\n", yeniMusteri.musteriAd, yeniMusteri.musteriNo, yeniMusteri.sifre);
}

void musteriGiris(){
    FILE *fPtr;
    FILE *f2Ptr;
    musteri musteriGiris;
    hesap hesapBilgi;
    hesap hesaplar;
    int sifre,girisSecim,musteriTip,sayac=1,*musteriHesaplari,secilenHesap,secilenIslem;

    musteriHesaplari = (int *) malloc(sizeof(int)*100); //BIRDEN FAZLA HESABI OLAN MUSTERILER ICIN DIZI

    menu3:
    printf("\n 1-Bireysel Musteri Girisi\n");
    printf(" 2-Kurumsal Musteri Girisi\n->");
    scanf("%d",&musteriTip);

    switch (musteriTip){
        case 1:
            printf("\n Musteri Numaranizi Giriniz [8 Hane]: ");
            scanf("%8d", &musteriGiris.musteriNo);
            if ((fPtr = fopen("bireyselMusteri.txt", "r+")) == NULL) puts("Dosya Acilamadi.");
            fseek(fPtr, (musteriGiris.musteriNo - 1) * sizeof(musteriGiris), SEEK_SET);  //MUSTERIYE AIT VERININ DOSYADAN OKUNMASI
            fread(&musteriGiris, sizeof(musteriGiris), 1, fPtr);
            fclose(fPtr); break;
        case 2:
            printf("\n Musteri Numaranizi Giriniz [8 Hane]: ");
            scanf("%8d", &musteriGiris.musteriNo);
            if ((fPtr = fopen("kurumsalMusteri.txt", "r+")) == NULL) puts("Dosya Acilamadi.");
            fseek(fPtr, (musteriGiris.musteriNo - 1) * sizeof(musteriGiris), SEEK_SET);
            fread(&musteriGiris, sizeof(musteriGiris), 1, fPtr);
            fclose(fPtr); break;
        default: printf("\a\n\t!Hatali Giris!\t Lutfen Tekrar Giris Yapiniz.\n\n"); goto menu3;
    }

    printf(" Sifrenizi Giriniz [4 Hane]: "); // SIFRE KONTROLU
    scanf("%4d", &sifre);
    system("cls");
    if (sifre != musteriGiris.sifre){
        printf("\a\n\n!HATALI GIRIS! Lutfen Tekrar Giris Yapiniz.\n\n");
        goto menu3;
        }
    printf("\n\tGiris Basarili! %c\n\n\tSayin %s, Hosgeldiniz!\n", 1, musteriGiris.musteriAd);
    menu4:
    printf("\n\t%c%c%c%c%c%c%c%c MUSTERI ISLEMLERI %c%c%c%c%c%c%c%c\n\n",4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4);

    printf(" 1-Yeni Hesap Ac\n");
    printf(" 2-Hesap Islemleri\n");
    printf(" 0-Ana Menuye Don\n->");
    scanf("%d", &girisSecim);

    switch(girisSecim){
        case 1:
            system("cls");
            if ((f2Ptr = fopen("musteriHesap.txt", "a+")) == NULL) puts("Dosya Acilamadi.");
            hesapBilgi.hesapNo = (rand()%89999999)+10000000;  //HESAP NUAMARSI ATAMASI
            hesapBilgi.hesapKisi = musteriGiris.musteriNo;
            printf("\n\tBasarili!\t%d. Hesap Numaraniz: %d\n",sayac, hesapBilgi.hesapNo);
            hesapBilgi.hesapBakiye = 0.0;
            fwrite(&hesapBilgi, sizeof(hesapBilgi), 1, f2Ptr); //HESAP BILGILERININ DOSYAYA YAZILMASI
            sayac++;
            fclose(f2Ptr);
            goto menu4;
        case 2:
            menu7:
                sayac =1;
                if ((f2Ptr = fopen("musteriHesap.txt", "r+")) == NULL) puts("Dosya Acilamadi.");
                while(fread(&hesaplar, sizeof(hesapBilgi), 1, f2Ptr) != 0){
                    if(musteriGiris.musteriNo == hesaplar.hesapKisi){
                        printf("\n\t%d-> Hesap Numarasi: %d, Bakiye: %.2f\n", sayac, hesaplar.hesapNo, hesaplar.hesapBakiye);
                        *(musteriHesaplari+(sayac-1)) = hesaplar.hesapNo;
                        sayac++;
                    }
                }
                fclose(f2Ptr);
                musteriHesaplari = realloc(musteriHesaplari,sizeof(int)*(sayac-1)); //MUSTERININ SAHIP OLDUGU HESAP SAYISININ YENIDEN BOYUTLANDIRILMASI

                menu5:
                    if(sayac == 1){
                        printf("\a\n\t!HATA!\tHesabiniz Bulunmamaktadir. Lutfen Once Hesap Aciniz.\n\n");
                        goto menu4;
                    }else{
                        printf("\n *Islem Yapmak Istediginiz Hesaba Ait Hesap Kodunu Giriniz [Ornek:1]: ");
                        scanf("%d", &secilenHesap);
                        menu6:
                        if(*(musteriHesaplari+(secilenHesap-1)) >= 10000000 && *(musteriHesaplari+(secilenHesap-1)) <= 99999999){
                            printf("\n\t%c%c%c%c%c%c HESAP ISLEMLERI %c%c%c%c%c%c\n\n",4,4,4,4,4,4,4,4,4,4,4,4);

                            printf(" 1-Para Yatirma\n");
                            printf(" 2-Para Cekme\n");
                            printf(" 3-Hesaba Havale\n");
                            printf(" 4-Hesap Ozeti\n");
                            printf(" 5-Hesabi Kapat\n");
                            printf(" 0-Ana Menuye Don\n->");
                            scanf("%d", &secilenIslem);

                            switch(secilenIslem){
                                case 1:paraYatirma(*(musteriHesaplari+(secilenHesap-1))); goto menu7;
                                case 2:paraCekme(*(musteriHesaplari+(secilenHesap-1)), musteriTip); goto menu7;
                                case 3:hesapHavale(*(musteriHesaplari+(secilenHesap-1)), musteriTip); goto menu7;
                                case 4:dekontOku(*(musteriHesaplari+(secilenHesap-1)));goto menu7;
                                case 5:hesapKapama(*(musteriHesaplari+(secilenHesap-1)));goto menu7;
                                case 0:break;
                                default:system("cls");printf("\a\t!Hatali Giris!\t Lutfen Tekrar Giris Yapiniz.\n"); sayac==0;goto menu7;
                            }

                        }else{
                            printf("\a\n\t!Hatali Giris!\t Lutfen Tekrar Giris Yapiniz.\n\n");
                            goto menu5;
                        }
                    }
        case 0: system("cls");break;
        default: system("cls"); printf("\a\n\t!Hatali Giris!\t Lutfen Tekrar Giris Yapiniz.\n\n"); goto menu4;
    }
}

float limitOgren(int ogrenilecekHesap){
    time_t s, val = 1;
    struct tm* current_time;
    s = time(NULL);
    current_time = localtime(&s); // TARIH FONKSIYONLARI

    FILE *fPtr;
    fPtr = fopen("dekont.txt", "r+");
    dekont dekontlar;
    float toplamCekilen=0;

    while(fread(&dekontlar, sizeof(dekontlar), 1, fPtr) != 0){
        if(dekontlar.dekontHesap == ogrenilecekHesap){
            if(dekontlar.islemTipi == 1){
                if(dekontlar.gun == current_time->tm_mday && dekontlar.ay == (current_time->tm_mon + 1) && dekontlar.yil ==(current_time->tm_year + 1900)){
                    toplamCekilen += dekontlar.miktar; // GUNLUK CEKIM TOPLAMI
                }
            }
        }
    }
    fclose(fPtr);
    return toplamCekilen;
}

void dekontOku(int okunacakHesap){
    FILE *fPtr;
    fPtr = fopen("dekont.txt", "r+");
    dekont dekontlar;
    system("cls");
    printf("\n   '%d' Numarali Hesap Ozeti: \n", okunacakHesap);
    while(fread(&dekontlar, sizeof(dekontlar), 1, fPtr) != 0){
        if(dekontlar.dekontHesap == okunacakHesap){
            switch(dekontlar.islemTipi){ //DEKONTUN EKRANA YAZDIRILMASI
                case 1:
                    printf("\n   [%d:%d:%d] %d.%d.%d Tarihinde %.2f Tutarinda Para Cekilmistir.\n", dekontlar.saat, dekontlar.dakika, dekontlar.saniye, dekontlar.gun, dekontlar.ay, dekontlar.yil, dekontlar.miktar);
                    break;
                case 2:
                    printf("\n   [%d:%d:%d] %d.%d.%d Tarihinde %.2f Tutarinda Para Yatirilmistir.\n", dekontlar.saat, dekontlar.dakika, dekontlar.saniye, dekontlar.gun, dekontlar.ay, dekontlar.yil, dekontlar.miktar);
                    break;
                case 3:
                    printf("\n   [%d:%d:%d] %d.%d.%d Tarihinde %.2f Tutarinda Havale Gonderilmistir.\n", dekontlar.saat, dekontlar.dakika, dekontlar.saniye, dekontlar.gun, dekontlar.ay, dekontlar.yil, dekontlar.miktar);
                    break;
                case 4:
                    printf("\n   [%d:%d:%d] %d.%d.%d Tarihinde %.2f Tutarinda Havale Gelmistir.\n", dekontlar.saat, dekontlar.dakika, dekontlar.saniye, dekontlar.gun, dekontlar.ay, dekontlar.yil, dekontlar.miktar);
                    break;
            }
        }
    }
    fclose(fPtr);
}

void dekontYaz(int dekontHesap, int islemTipi, float miktar){
    time_t s, val = 1;
    struct tm* current_time;
    s = time(NULL);
    current_time = localtime(&s);   //TARIH FONKSIYONLARI

    FILE *fPtr;
    fPtr = fopen("dekont.txt", "a+");
    //TARIHIN ALINMASI
    dekont yazilacakDekont;
    yazilacakDekont.dekontHesap = dekontHesap;
    yazilacakDekont.islemTipi = islemTipi;
    yazilacakDekont.miktar = miktar;
    yazilacakDekont.gun = current_time->tm_mday;
    yazilacakDekont.ay = (current_time->tm_mon + 1);
    yazilacakDekont.yil = (current_time->tm_year + 1900);
    yazilacakDekont.saniye = current_time->tm_sec;
    yazilacakDekont.dakika = current_time->tm_min;
    yazilacakDekont.saat = current_time->tm_hour;

    fwrite(&yazilacakDekont, sizeof(yazilacakDekont), 1, fPtr); // DEKONTUN DOSYAYA KAYIT EDILMESI
    fclose(fPtr);
}

void paraCekme(int hesapNo, int musteriTipi){
    hesap cekilecekHesap;
    FILE *fPtr;
    FILE *f2Ptr;
    fPtr = fopen("musteriHesap.txt", "r+");
    int sayac = 0;
    float cekilecekMiktar;
    float gunlukCekilen = limitOgren(hesapNo); //LIMIT DURUMUNUN OGRENILMESI

    while(fread(&cekilecekHesap, sizeof(cekilecekHesap), 1, fPtr) != 0){
        sayac++;
        if(hesapNo == cekilecekHesap.hesapNo){
            menu8:
                printf("\n\tCekilecek Miktari Giriniz >>> ");
                scanf("%f",&cekilecekMiktar);
                system("cls");
                if(cekilecekMiktar > cekilecekHesap.hesapBakiye){ //LIMIT KONTROLU
                    printf("\a\n\t!Yetersiz Bakiye!\tLutfen Tekrar Giriniz.\n");
                    goto menu8;
                }
                if(musteriTipi == 1){//KURUMSAL
                    if((gunlukCekilen + cekilecekMiktar) > 750){
                        printf("\a\n\t!Gunluk Cekim Limitini Astiniz!\n\n\tGunluk Cekim Limiti 750'dir Lutfen Tekrar Giriniz.\n");
                        printf("\n\t[Maksimum Cekebileceginiz Tutar: %.2f]\n", (750 - gunlukCekilen));
                        goto menu8;
                    }
                }else{//BIREYSEL
                    if((gunlukCekilen + cekilecekMiktar) > 1500){
                        printf("\a\n\t!Gunluk Cekim Limitini Astiniz!\n\t Gunluk Cekim Limiti 1500'dur Lutfen Tekrar Giriniz.\n");
                        printf("\n\t[Maksimum Cekebileceginiz Tutar: %.2f]\n", (750 - gunlukCekilen));
                        goto menu8;
                    }
                }

                printf("\n   Islem Basarili! %c\n\n\t%.2f Tutari '%d' Numarali Hesaptan Cekilmistir.\n\n",1,cekilecekMiktar,cekilecekHesap.hesapNo);


                cekilecekHesap.hesapBakiye -= cekilecekMiktar; //GONDERILEN PARANIN HESAPTAN DUSURULMESI
                break;
        }
    }
    fclose(fPtr);

    f2Ptr = fopen("musteriHesap.txt", "r+"); //MUSTERI ISLEMLERININ KAYIT EDILMESI
    fseek(f2Ptr, (sayac-1)*sizeof(cekilecekHesap), SEEK_SET);
    fwrite(&cekilecekHesap, sizeof(cekilecekHesap), 1, f2Ptr);
    fclose(f2Ptr);

    dekontYaz(cekilecekHesap.hesapNo, 1, cekilecekMiktar);  // DEKONTUN DOSYAYA KAYIT EDILMESI

    //BANKA GELIR GIDER RAPORU
    int gider = -1 * cekilecekMiktar;
    FILE *f3Ptr;
    f3Ptr = fopen("rapor.txt", "a+");
    fwrite(&gider, sizeof(int), 1, f3Ptr);
    fclose(f3Ptr);
}

void paraYatirma(int hesapNo){
    hesap yatirilacakHesap;
    FILE *fPtr;
    FILE *f2Ptr;
    fPtr = fopen("musteriHesap.txt", "r+");
    int sayac = 0;
    float yatirilacakMiktar;
    while(fread(&yatirilacakHesap, sizeof(yatirilacakHesap), 1, fPtr) != 0){
        sayac++;
        if(hesapNo == yatirilacakHesap.hesapNo){
            menu8:
                printf("\n\tYatirilacak Miktari Giriniz >>> ");
                scanf("%f",&yatirilacakMiktar);
                yatirilacakHesap.hesapBakiye += yatirilacakMiktar; //ALICI HESABIN BAKIYESININ TOPLANMASI
                fclose(fPtr);
                break;
        }
    }
    system("cls");
    printf("\n   Islem Basarili! %c\n\n\t%.2f Tutari '%d' Numarali Hesaba Yatirilmistir.\n\n",1,yatirilacakMiktar,yatirilacakHesap.hesapNo);

    f2Ptr = fopen("musteriHesap.txt", "r+");
    fseek(f2Ptr, (sayac-1)*sizeof(yatirilacakHesap), SEEK_SET);
    fwrite(&yatirilacakHesap, sizeof(yatirilacakHesap), 1, f2Ptr);
    fclose(f2Ptr);

    dekontYaz(yatirilacakHesap.hesapNo, 2, yatirilacakMiktar);

    //BANKA GELIR GIDER RAPORU
    int gelir = yatirilacakMiktar;
    FILE *f3Ptr;
    f3Ptr = fopen("rapor.txt", "a+");
    fwrite(&gelir, sizeof(int), 1, f3Ptr);
    fclose(f3Ptr);
}

void hesapKapama(int hesapNo){
    FILE *fPtr;
    FILE *f2Ptr;
    fPtr = fopen("musteriHesap.txt", "r+");
    hesap silinecekHesap;
    int sayac = 0;
    while(fread(&silinecekHesap, sizeof(silinecekHesap), 1, fPtr) != 0){
        sayac++;
        if(hesapNo == silinecekHesap.hesapNo){
            if(silinecekHesap.hesapBakiye != 0){
                system("cls");
                printf("\a\n\n\t!HESAP SILINEMEDI!\n\tHesabi Silebilmeniz Icin Bakiyenin 0 Olmasi Gerekmektedir.\n\n");
                fclose(fPtr);
                return;
            }
            system("cls");
            printf("\n\n\tIslem Basarili! %c\n\n\t'%d' Numarali Hesabiniz Kapanmistir.\n\n",1,silinecekHesap.hesapNo);
            silinecekHesap.hesapKisi = 0;
            silinecekHesap.hesapNo = 0;
            break;
        }
    }
    fclose(fPtr);

    f2Ptr = fopen("musteriHesap.txt", "r+");
    fseek(f2Ptr, (sayac-1)*sizeof(silinecekHesap), SEEK_SET);
    fwrite(&silinecekHesap, sizeof(silinecekHesap), 1, f2Ptr);
    fclose(f2Ptr);
}

void hesapHavale(int hesapNo, int musteriTipi){
    FILE *fPtr;
    FILE *f2Ptr;
    FILE *fPtrw;
    FILE *f2Ptrw;
    fPtr = fopen("musteriHesap.txt", "r+");
    f2Ptr = fopen("musteriHesap.txt", "r+");
    hesap gonderenHesap;
    hesap gonderilenHesap;
    int sayac = 0,sayac2 = 0, gonderilenNo, bulundu=0;
    float gonderilecekTutar;
    printf("\n\tGonderilecek Hesabin Numarasini Giriniz >>> ");
    scanf("%d", &gonderilenNo);

    while(fread(&gonderilenHesap, sizeof(gonderilenHesap), 1, f2Ptr) != 0){
        sayac2++;
        if(gonderilenNo == gonderilenHesap.hesapNo){
            bulundu = 1;
            break;
        }
    }
    fclose(f2Ptr);
    if(bulundu == 0){
        system("cls");
        printf("\a\n\n\t!HESAP BULUNAMADI!\n\n");
        return;
    }

    while(fread(&gonderenHesap, sizeof(gonderenHesap), 1, fPtr) != 0){
        sayac++;
        if(hesapNo == gonderenHesap.hesapNo){
            menu9:
                printf("\n\tGonderilecek Tutari Giriniz >>> "); //BAKIYE KONTROL
                scanf("%f", &gonderilecekTutar);
                if(gonderilecekTutar > gonderenHesap.hesapBakiye){
                    printf("\a\n\n\t!YETERSIZ BAKIYE! Lutfen Farkli Bir Tutar Giriniz.\n\n");
                    goto menu9;
                }
                break;
        }
    }
    fclose(fPtr);

    float gonderilenTutar = gonderilecekTutar;

    if(musteriTipi == 1){
        gonderilenTutar -= (gonderilenTutar*2/100); //BIREYSEL HAVALE KESINTISI
        system("cls");
        printf("\n   Islem Basarili! %c\n\n\t'%d' Numarali Hesaba %.2f Tutarinda Para Gonderilmistir.\n",1,gonderilenHesap.hesapNo,gonderilenTutar);
        printf("\t[Kesinti Tutari: %.2f]\n\n",((gonderilenTutar/100)*2));
    }
    else{
        system("cls");
        printf("\n   Islem Basarili! %c\n\n\t'%d' Numarali Hesaba %.2f Tutarinda Para Gonderilmistir\n\n",1,gonderilenHesap.hesapNo,gonderilenTutar);
    }

    dekontYaz(gonderenHesap.hesapNo, 3, gonderilecekTutar);
    dekontYaz(gonderilenHesap.hesapNo, 4, gonderilenTutar);

    gonderenHesap.hesapBakiye -= gonderilecekTutar;
    gonderilenHesap.hesapBakiye += gonderilenTutar;


    f2Ptrw = fopen("musteriHesap.txt", "r+");
    fseek(f2Ptrw, (sayac2-1)*sizeof(gonderilenHesap), SEEK_SET);
    fwrite(&gonderilenHesap, sizeof(gonderilenHesap), 1, f2Ptrw);
    fclose(f2Ptrw);

    fPtrw = fopen("musteriHesap.txt", "r+");
    fseek(fPtrw, (sayac-1)*sizeof(gonderenHesap), SEEK_SET);
    fwrite(&gonderenHesap, sizeof(gonderenHesap), 1, fPtrw);
    fclose(fPtrw);
}

void bankaRaporAl(){
    FILE *f3Ptr;
    int donen,gelir=0,gider=0;
    if ((f3Ptr = fopen("rapor.txt", "r+")) == NULL) puts("Dosya Acilamadi.");
    while(fread(&donen, sizeof(int), 1, f3Ptr) != 0){
        if(donen>0){
            gelir+=donen;
        }else{
            gider-=donen;
        }
    }
    system("cls");
    printf("\n    *BANKA RAPORU*\n");
    printf("\n\t Banka Geliri: %d\n\n\t Banka Gideri: %d\n\n\t Bankadaki Toplam Para: %d\n", gelir, gider, gelir-gider);
    fclose(f3Ptr);
}

int main(){
    srand(time(NULL));
    int secenek;
    menu1:
        printf("\n\t%c%c%c%c%c%c%c MENU %c%c%c%c%c%c%c\n\n",4,4,4,4,4,4,4,4,4,4,4,4,4,4);
        printf(" 1-Musteri Ekle\n");
        printf(" 2-Musteri Giris\n");
        printf(" 3-Banka Gelir-Gider Raporu\n");
        printf(" 0-Cikis icin '0' Giriniz\n->");
        scanf("%d", &secenek);
        switch(secenek){
            case 1:musteriEkle(); goto menu1;
            case 2:musteriGiris(); goto menu1;
            case 3:bankaRaporAl(); goto menu1;
            case 0:exit(0);break;
            default:system("cls");printf("\a\n\t!Hatali Giris!\t Lutfen Tekrar Giris Yapiniz.\n"); goto menu1;
        }
    return 0;
}

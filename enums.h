#ifndef ENUMS_H
#define ENUMS_H

struct Sprzedaz {
  enum eData {
    Id,
    FirmaId,
    KontrahentId,
    DowodSprzedazy,
    DataSprzedazy,
    DataWystawienia,
    K_10,
    K_11,
    K_12,
    K_13,
    K_14,
    K_15,
    K_16,
    K_17,
    K_18,
    K_19,
    K_20

  };
};

struct Zakup {
  enum eData {
    Id,
    FirmaId,
    KontrahentId,
    DowodZakupu,
    DataZakupu,
    DataWplywu,
    K_43,
    K_44,
    K_45,
    K_46
  };
};


struct MojaFirma {
  enum eData { Id, Skrot, Nazwa, NIP, Adres, Email, LiczbaKolumn };
};

struct Kontrahent {
  enum eData { Id, NazwaKontrahenta, NrKontrahenta, AdresKontrahenta, LiczbaKolumn };
};

#endif // ENUMS_H

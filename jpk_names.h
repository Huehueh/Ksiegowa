#ifndef JPK_NAMES_H
#define JPK_NAMES_H

#include <QString>
#include "enums.h"

enum Fields
{
    Subject,
    Name,
    Identifier,
    Email,
    RowName,
    OrdinalNumber,
    ContractorNumber,
    ContractorName,
    ContractorAddress,
    Evidence,
    Date1,
    Date2,
    NetAmount,
    Tax,
    Ctrl,
    RowCount,
    TaxSum
};

namespace Company
{
QMap<Fields, QString> Names =
{
    {Subject, "tns:Podmiot1"},
    {Name, "tns:PelnaNazwa"},
    {Idetifier, "tns:NIP"},
    {Email, "tns:Email"}
};
}

namespace Purchase
{
    QMap<Fields, QString> Names =
    {
        {RowName, "tns:ZakupWiersz"},
        {OrdinalNumber, "tns:LpSprzedazy"},
        {ContractorNumber, "tns:NrKontahenta"},
        {ContractorName, "tns:NazwaKontahenta"},
        {ContractorAddress, "tns:AdresKontahenta"},
        {Evidence, "tns:DowodSprzedazy"},
        {Date1, "tns:DataSprzedazy"},
        {Date2, "tns:DataWystawienia"},
        {NetAmount, "tns:K_19"},
        {Tax, "tns:K_20"},
        {Ctrl, "tns::SprzedazCtrl"},
        {RowCount, "tns:LiczbaWierszySprzedazy"},
        {TaxSum, "tns::PodatekNalezny"}
    };
}

namespace Sale
{
QMap<Fields, QString> Names =
{
    {RowName, "tns:SprzedazWiersz"},
    {OrdinalNumber, "tns:LpZakupu"},
    {ContractorNumber, "tns:NrDostawcy"},
    {ContractorName, "tns:NazwaDostawcy"},
    {ContractorAddress, "tns:AdresDostawcy"},
    {Evidence, "tns:DowodZakupu"},
    {Date1, "tns:DataZakupu"},
    {Date2, "tns:DataWplywu"},
    {NetAmount, "tns:K_45"},
    {Tax, "tns:K_46"},
    {Ctrl, "tns::ZakupCtrl"},
    {RowCount, "tns:LiczbaWierszyZakupow"},
    {TaxSum, "tns::PodatekNaliczony"}
};
}


#endif // JPK_NAMES_H

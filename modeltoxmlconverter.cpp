#include "modeltoxmlconverter.h"

#include "enums.h"
#include "jpk_names.h"

ModelToXmlConverter::ModelToXmlConverter(const QModelIndex& companyData, int year, int month) : m_pWriter(nullptr)
{
    m_pWriter = new QXmlStreamWriter(&output);
    m_pWriter->setAutoFormatting(true);
    m_pWriter->writeStartDocument();

    // Podmiot1
    m_pWriter->writeStartElement(Company::Names.value(Fields::Subject));

    auto name = companyData.data(MojaFirma::Nazwa);
}

void Model

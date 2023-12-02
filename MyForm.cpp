#include "MyForm.h"
#include "DojiChart.h"
#include "CandleStickReader.h"
#include "Form2.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]

int main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	CIS4930::MyForm form;
	Application::Run(% form);
}

System::Void CIS4930::MyForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
    for each (String^ item in selectedCandleSticks) {
        DojiChart^ chart = gcnew DojiChart();
        candleStickBois = CandleStickReader->ReadStock(item, dateTimePicker1->Value, dateTimePicker2->Value);
        chart->chart1->DataSource = candleStickBois; // Set the DataSource property for the chart
        chart->Show();
    }
    selectedCandleSticks->Clear();
}

System::Void CIS4930::MyForm::radioButton1_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
    String^ period = "Day";
    comboBox1->Items->Clear();
    

    for each (FileInfo ^ file in Files)
    {
        if (file->Name->Contains(period))
        {
            comboBox1->Items->Add(file->Name);
        }
    }

    comboBox1->Items->Add(comboBox1);

}

System::Void CIS4930::MyForm::comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
}

System::Void CIS4930::MyForm::radioButton2_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
    String^ period = "Week";
    comboBox1->Items->Clear();

    for each (FileInfo ^ file in Files)
    {
        if (file->Name->Contains(period))
        {
            comboBox1->Items->Add(file->Name);
        }
    }

    comboBox1->Items->Add(comboBox1);
}

System::Void CIS4930::MyForm::radioButton3_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
    String^ period = "Month";
    comboBox1->Items->Clear();

    for each (FileInfo ^ file in Files)
    {
        if (file->Name->Contains(period))
        {
            comboBox1->Items->Add(file->Name);
        }
    }

    comboBox1->Items->Add(comboBox1);
}

System::Void CIS4930::MyForm::button2_Click(System::Object^ sender, System::EventArgs^ e)
{
    selectedCandleSticks->Add(comboBox1->Text);// add the selected ticker to the list
    comboBox1->SelectedIndex = -1;// reset the selected item
    comboBox1->Text = String::Empty;// reset the textbox
}

#pragma once

#include "Recognizer.h"
#include "SingleDojiRecognizer.h"
#include "DoubleDojiRecognizer.h"

namespace CIS4930 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Windows::Forms::DataVisualization::Charting;

	/// <summary>
	/// Summary for MyForm1
	/// </summary>
	public ref class DojiChart : public System::Windows::Forms::Form
	{
		List<candleStick^>^ CandleStick = gcnew List<candleStick^>();

	public:
		DojiChart(void)
		{
			InitializeComponent();
			initializeRecognizer();
			chart1->Series["OHLC"]->XValueMember = "Date"; // Sets the values on the x-axis to the date type
			chart1->Series["OHLC"]->YValuesPerPoint = 4; // Sets the amount of variables on the y-axis from its initial 1 to 4
			chart1->Series["OHLC"]->YValueMembers = "High, Low, Open, Close"; // Defines what the name of the variables the y-axis should be looking for
			chart1->ChartAreas["OHLC"]->AxisX->MajorGrid->LineWidth = 0; // Determines the line width for the x-axis on the chart
			chart1->ChartAreas["OHLC"]->AxisY->MajorGrid->LineWidth = 0; // Determines the line width for the y-axis on the chart

			chart1->Series["OHLC"]->CustomProperties = "PriceUpColor=Green,PriceDownColor=Red"; // Sets the color for the up and down candlesticks to green and red, respectively

			chart1->DataBind(); // Binds the candlestick reader to the doji chart so that the data can be displayed properly

			chart1->ChartAreas["OHLC"]->AxisX->ScaleView->Zoomable = true; // Enables the zoom for the x-axis
			chart1->ChartAreas["OHLC"]->AxisY->ScaleView->Zoomable = true; // Enables the zoom for the y-axis
			chart1->ChartAreas["OHLC"]->CursorX->AutoScroll = true; // Allows the chart to scroll if there is enough data present
			chart1->ChartAreas["OHLC"]->CursorX->IsUserSelectionEnabled = true; // Allows the user to have control over what area on the x-axis they will zoom

		}
		
		List<aRecognizor^>^ recognizors = gcnew List<aRecognizor^>(32);

		List<aRecognizor^>^ DojiChart::initializeRecognizer()
		{
			aRecognizor^ recognizor;
			//MessageBox::Show("initializeRecognizer Called");// called

			recognizor = gcnew Recognizer_Bullish();
			recognizors->Add(recognizor);

			recognizor = gcnew Recognizer_Bearish();
			recognizors->Add(recognizor);

			recognizor = gcnew Recognizer_Neutral();
			recognizors->Add(recognizor);

			recognizor = gcnew Recognizer_NeutralDoji();
			recognizors->Add(recognizor);

			recognizor = gcnew Recognizer_Doji();
			recognizors->Add(recognizor);

			recognizor = gcnew Recognizer_DragonFly();
			recognizors->Add(recognizor);

			recognizor = gcnew Recognizer_GravestoneDoji();
			recognizors->Add(recognizor);

			recognizor = gcnew Recognizer_longLeggedDoji();
			recognizors->Add(recognizor);

			recognizor = gcnew Recognizer_Hammer();
			recognizors->Add(recognizor);

			recognizor = gcnew Recognizer_BullishHammer();
			recognizors->Add(recognizor);

			recognizor = gcnew Recognizer_BearishHammer();
			recognizors->Add(recognizor);

			recognizor = gcnew Recognizer_invertedHammer();
			recognizors->Add(recognizor);

			recognizor = gcnew Recognizer_bullishInvertedHammer();
			recognizors->Add(recognizor);

			recognizor = gcnew Recognizer_bearishInvertedHammer();
			recognizors->Add(recognizor);

			recognizor = gcnew Recognizer_Marubozu();
			recognizors->Add(recognizor);

			recognizor = gcnew Recognizer_blackMarubozu();
			recognizors->Add(recognizor);

			recognizor = gcnew Recognizer_whiteMarubozu();
			recognizors->Add(recognizor);

			recognizor = gcnew EngulfingBullishCandlestick_Recognizer();
			recognizors->Add(recognizor);

			recognizor = gcnew EngulfingBearishCandlestick_Recognizer();
			recognizors->Add(recognizor);

			comboBoxDoji->Items->Clear(); // This double checks to ensure that the combo box is clear before adding the doji types and patterns
			for each (aRecognizor ^ r in recognizors)
			{
				comboBoxDoji->Items->Add(r->patternName); // This is the line that actually adds the patterns or doji types
				//MessageBox::Show(r->patternName->ToString());
			}
			comboBoxDoji->Enabled = true;

			return recognizors;
		}

	public: Void updateChart()
	{
		List<candleStick^>^ dataSource = dynamic_cast<List<candleStick^>^>(chart1->DataSource); /// Assuming chartDoji is of type System::Windows::Forms::DataVisualization::Charting::Chart

		if (dataSource != nullptr && dataSource->Count > 0)
		{
			CandleStick = dataSource; /// Convert List to array for easier indexing

			// Update the chart area based on the data source
			{
				double maxY = findMaxHigh(CandleStick); /// Find the max value for the y-axis based on the stock file
				double minY = findMinLow(CandleStick); /// Find the min value for the y-axis based on the stock file

				double padding = 0.10 * (maxY - minY); /// Add padding to the chart to make it easier to see if there is a larger amount of data

				chart1->ChartAreas["OHLC"]->AxisY->Maximum = maxY + padding; /// Set the new max for the padding to ensure no data gets cut when the padding gets added
				chart1->ChartAreas["OHLC"]->AxisY->Minimum = minY - padding; /// Set the new min for the padding to ensure no data gets cut when the padding gets added
			}
		}
	}

	double findMaxHigh(List<candleStick^>^ candleSticks)
	{
		double maxHigh = Double::MinValue; /// Initialize with the smallest possible value

		for each (candleStick ^ cs in candleSticks)
		{
			if (cs->High > maxHigh)
			{
				maxHigh = cs->High;
			}
		}

		return maxHigh;
	}

	double findMinLow(List<candleStick^>^ candleSticks)
	{
		double minLow = Double::MaxValue; /// Initialize with the largest possible value

		for each (candleStick ^ cs in candleSticks)
		{
			if (cs->Low < minLow)
			{
				minLow = cs->Low;
			}
		}
		return minLow;
	}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~DojiChart()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;
	protected:
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::ComboBox^ comboBoxDoji;


	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->comboBoxDoji = (gcnew System::Windows::Forms::ComboBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->SuspendLayout();
			// 
			// chart1
			// 
			chartArea1->Name = L"OHLC";
			this->chart1->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(12, 12);
			this->chart1->Name = L"chart1";
			series1->ChartArea = L"OHLC";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Candlestick;
			series1->CustomProperties = L"PriceDownColor=Red, PriceUpColor=Lime";
			series1->Legend = L"Legend1";
			series1->Name = L"OHLC";
			series1->YValuesPerPoint = 4;
			this->chart1->Series->Add(series1);
			this->chart1->Size = System::Drawing::Size(882, 348);
			this->chart1->TabIndex = 0;
			this->chart1->Text = L"chart1";
			this->chart1->Click += gcnew System::EventHandler(this, &DojiChart::chart1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(74, 443);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(69, 16);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Doji Type:";
			this->label1->Click += gcnew System::EventHandler(this, &DojiChart::label1_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(750, 426);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(144, 38);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Return to Home";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &DojiChart::button1_Click);
			// 
			// comboBoxDoji
			// 
			this->comboBoxDoji->FormattingEnabled = true;
			this->comboBoxDoji->Location = System::Drawing::Point(149, 440);
			this->comboBoxDoji->Name = L"comboBoxDoji";
			this->comboBoxDoji->Size = System::Drawing::Size(215, 24);
			this->comboBoxDoji->TabIndex = 3;
			this->comboBoxDoji->SelectedIndexChanged += gcnew System::EventHandler(this, &DojiChart::comboBoxDoji_SelectedIndexChanged);
			//MessageBox::Show("???");
			// 
			// DojiChart
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(924, 482);
			this->Controls->Add(this->comboBoxDoji);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->chart1);
			this->Name = L"DojiChart";
			this->Text = L"DojiChart";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void dataGridView1_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
public: System::Void chart1_Click(System::Object^ sender, System::EventArgs^ e) {
}
public: System::Void CIS4930::DojiChart::comboBoxDoji_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
	//MessageBox::Show("called?");
	updateChart(); // This calls the updateChart so that when another index is selected in the combo box the chart is updated with the new data and padding is added
	chart1->Annotations->Clear(); // This clears the previous annotations from the chart when a new index is selected

	aRecognizor^ recognizor = recognizors[comboBoxDoji->SelectedIndex]; // Get the selected doji recognizor from the comboBox
	//MessageBox::Show(comboBoxDoji->SelectedIndex.ToString());
	List<int>^ retcon = recognizor->recognize(CandleStick); // Recognize the patterns in the candlestick data
	for each (int i in retcon) // This is the loop that adds the actual rectangle next to the doji in the chart
	{
		//MessageBox::Show(i.ToString());
		RectangleAnnotation^ ra = gcnew RectangleAnnotation(); // This sets the shape
		ra->Text = recognizor->patternName; // This sets the correct name inside the rectangle
		ra->AnchorDataPoint = chart1->Series["OHLC"]->Points[i]; // This sets the position for the rectangle to be
		chart1->Annotations->Add(ra); // This is the line that actually adds the rectangle
	}
}
};
}

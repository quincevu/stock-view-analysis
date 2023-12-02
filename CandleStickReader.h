#pragma once
#include "CandleStick.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::IO;
using namespace System::Windows::Forms;
namespace CIS4930 {
    public ref class candleStickReader
    {
    private:
        static String^ dataFolder = ".\\x64\\Debug\\Stock Data";
        List<candleStick^>^ candleStickBois;

    public:
        candleStickReader()
        {
            candleStickBois = gcnew List<candleStick^>(256);
        }

        List<candleStick^>^ ReadCandleStickBois(String^ csvFilename, DateTime startDate, DateTime endDate)
        {
            array<wchar_t>^ separator = gcnew array<wchar_t>{ '-', '/', ',', '\"' };
            array<String^>^ lines = File::ReadAllLines(csvFilename);
            String^ header = lines[0];

            candleStickBois = gcnew List<candleStick^>();

            if (header == "\"Ticker\",\"Period\",\"Date\",\"Open\",\"High\",\"Low\",\"Close\",\"Volume\"")
            {
                for (int l = 1; l < lines->Length; l++)
                {
                    String^ line = lines[l]->Trim();
                    array<String^>^ substrings = line->Split(separator, StringSplitOptions::RemoveEmptyEntries);

                    String^ dayMonth = substrings[2];
                    String^ monthStr = dayMonth->Substring(0, 3);
                    String^ dayStr = dayMonth->Substring(4);
                    int day = Int32::Parse(dayStr);

                    int month = 0;
                    if (monthStr == "Jan") month = 1;
                    else if (monthStr == "Feb") month = 2;
                    else if (monthStr == "Mar") month = 3;
                    else if (monthStr == "Apr") month = 4;
                    else if (monthStr == "May") month = 5;
                    else if (monthStr == "Jun") month = 6;
                    else if (monthStr == "Jul") month = 7;
                    else if (monthStr == "Aug") month = 8;
                    else if (monthStr == "Sep") month = 9;
                    else if (monthStr == "Oct") month = 10;
                    else if (monthStr == "Nov") month = 11;
                    else if (monthStr == "Dec") month = 12;

                    int year = Int32::Parse(substrings[3]);

                    DateTime date = DateTime(year, month, day);

                    if (date.CompareTo(startDate) >= 0 && date.CompareTo(endDate) < 0)
                    {
                        double open = Double::Parse(substrings[4]);
                        double high = Double::Parse(substrings[5]);
                        double low = Double::Parse(substrings[6]);
                        double close = Double::Parse(substrings[7]);
                        long volume = Int64::Parse(substrings[8]);

                        open = Math::Round(open, 2);
                        high = Math::Round(high, 2);
                        low = Math::Round(low, 2);
                        close = Math::Round(close, 2);

                        candleStick^ candlestick = gcnew candleStick(date, open, high, low, close, volume);
                        candleStickBois->Add(candlestick);
                    }
                }
            }
            return candleStickBois;
        }

        List<candleStick^>^ ReadStock(String^ ticker, DateTime startDate, DateTime endDate)
        {
            String^ csvFilename = String::Format("{0}\\{1}", dataFolder, ticker);

            candleStickBois = ReadCandleStickBois(csvFilename, startDate, endDate);

            return candleStickBois;
        }
    };
}
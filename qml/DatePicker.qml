import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

Item
{
    property int year: 1990
    property int month: 1
    property int day: 1
    property int maxAge: 100

    property date selectedDate

    function select()
    {
        selectedDate = new Date(_year.selectedYear(), _months.currentIndex, _day.currentIndex +1)
    }

    function daysInMonth(month,year) {
        return new Date(year, month, 0).getDate();
    }

    RowLayout
    {
        anchors.fill: parent

        YearColumn
        {
            id: _year
            model: new Array(maxAge)
            minYear: new Date().getFullYear() - maxAge
            currentIndex: year - minYear - 1
            Layout.preferredWidth: app.sizes.xxLarge * 2
            Layout.fillHeight: true
        }

        VerticalLine { opacity: 0.3 }

        MonthColumn
        {
            id: _months
            model: 12
            currentIndex: month - 1
            Layout.preferredWidth: app.sizes.xxLarge * 2
            Layout.fillHeight: true

            onCurrentItemChanged: _day.model = daysInMonth(_year.currentIndex, _months.currentIndex)
        }

        VerticalLine { opacity: 0.3 }

        DayColumn
        {
            id: _day
            model: daysInMonth(_year.currentIndex, _months.currentIndex)
            currentIndex: day - 1
            Layout.preferredWidth: app.sizes.xxLarge * 2
            Layout.fillHeight: true
        }
    }
}

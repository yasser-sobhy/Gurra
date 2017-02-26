import QtQuick 2.0

Item
{
    property string primary: fontAwesome // default icon font

    property string afiado
    property string brankit
    property string entipoPlus
    property string feather
    property string fontAwesome: _fontAwesome.name
    property string hawcons
    property string icomoon: _icomoon.name
    property string linecons
    property string material
    property string meteocons
    property string octicons
    property string typicons
    property string wpzoom

    property string afiado_file: "assets/fonts/afiado.ttf"
    property string brankit_file: "assets/fonts/brankit.ttf"
    property string entipoPlus_file: "assets/fonts/entipoPlus.ttf"
    property string feather_file: "assets/fonts/feather.ttf"
    property string fontAwesome_file: "assets/fonts/fontawesome.ttf"
    property string hawcons_file: "assets/fonts/hawcons.ttf"
    property string icomoon_file: "assets/fonts/icomoon.ttf"
    property string linecons_file: "assets/fonts/linecons.ttf"
    property string material_file: "assets/fonts/material.ttf"
    property string meteocons_file: "assets/fonts/meteocons.ttf"
    property string octicons_file: "assets/fonts/octicons.ttf"
    property string typicons_file: "assets/fonts/typicons.ttf"
    property string wpzoom_file: "assets/fonts/wpzoom.ttf"

    FontLoader
    {
        id: _fontAwesome
        source: fontAwesome_file
    }

    FontLoader
    {
        id: _icomoon
        source: icomoon_file
    }
}

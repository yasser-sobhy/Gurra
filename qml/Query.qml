import QtQuick 2.0

QtObject {

    function makeQuery(query)
    {
        var result = ""

        for (var p in query)
        {
            if( typeof query[p] !== "function" )
                if(p !== "objectName"){
                    result += p + "=" + query[p] + ","
                }
        }

        result = result.substring(0, result.length - 1); // remove last comma
        return result
    }
}

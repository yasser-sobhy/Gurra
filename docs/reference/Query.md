#Query converts a JavaScript object into a query string.


    Query {
        id: query_mk
    }

    var query = {
    
        listing_id: search_listing_id,
        type: search_listing_type,
        area: search_area,
        color: search_color,
        brand_id: search_brand_id,
        year: search_year,
        make: search_make
    }
    
    app.pages.listings.params.search_query = query_mk.makeQuery(query)
    app.pushPage(app.pages.listings)
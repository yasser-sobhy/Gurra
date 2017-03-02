#Urls object groups together frequently used urls to increase readability and avoid mistyping.

    Urls
    {
        root: app.production? "http://www.example.com:8080" :   http://localhost:8080"
        
        pictures: app.production? "http://example.com/uploads/" : "http://localhost/uploads/"
    }

##Available Urls

###**root**: string

    default: empty string

###**users**: string
    default: empty string

###**config**: string
    default: empty string

###**updates **: string
    default: empty string

###**pictures**: string
    default: empty string

###**files**: string
    default: empty string

###**static_**: string
    default: empty string

###**socket**: string
    default: empty string

###**analitics**: string
    default: empty string

###**social**: string
    default: empty string


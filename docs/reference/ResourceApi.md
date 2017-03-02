#ResourceApi allows your app to execute RESTful operation on a web service

>   `ResourceApi` uses app's central `RestConsumer` using `app.restConsumer` to send requests and receive response 


##Properties

###**resource**: string
This property holds the resource on which `ResourceApi` will post requests

This resource will be appended to `app.restConsumer` root url. For example if `resource` is */images*  and `app.restConsumer` root url is *www.example.com* the resulting url will be *www.example.com/images*

###**promise**: SimplePromise
This property holds the promise that hold the callback functions

> You need not to change this property, it's assumed to be read-only

##Functions

###**get(what, query)**
Posts a GET request to `resource` to retrieve data. `what` may be a sub-resource  or empty string, `query` is a comma separated list of key-value pairs, query is optional.
	
	var my_query = "cat=international, type=sport"
	get("/latestnews", my_query)

###**get_one(id, query)**
Posts a GET request to `resource` to retrieve data. `id` is the id of the resource to get, `query` is a comma separated list of key-value pairs, query is optional.

        app.api.members.get_one(app.settings.member_id).then(function(data){
            console.log(data)
        })

###**list(query)**
Posts a GET request to `resource` to retrieve data. `query` is a comma separated list of key-value pairs, query is optional.

        app.api.images.list().then(function(data){
            console.log(data)
        })
        
###**create(data, query)**
Posts a POST request to `resource` to create a new resource. `data` is string to be posted, `query` is a comma separated list of key-value pairs, query is optional.

    var obj = {
        member_id: edit? member.member_id : 0,
        name: nameInput.text,
        mobile: phoneInput.text,
        email: emailInput.text,
        password: paswordInput.text,
        created_at: edit? member.created_at : new Date().toLocaleString(Qt.locale("en_US"), "dd/MM/yyyy hh:mm:ss"),
        updated_at: edit? member.updated_at : new Date().toLocaleString(Qt.locale("en_US"), "dd/MM/yyyy hh:mm:ss")
    }
    
    app.api.members.create(JSON.stringify(obj)).then(function(data){
	    console.log(data)
    })

###**save(id, data, query)**
Posts a PUT request to `resource` to edit an existing resource. `id` is the id of the resource to edit, `data` is string to be posted, `query` is a comma separated list of key-value pairs, query is optional.

    var obj = {
        member_id: edit? member.member_id : 0,
        name: nameInput.text,
        mobile: phoneInput.text,
        email: emailInput.text,
        password: paswordInput.text,
        created_at: edit? member.created_at : new Date().toLocaleString(Qt.locale("en_US"), "dd/MM/yyyy hh:mm:ss"),
        updated_at: edit? member.updated_at : new Date().toLocaleString(Qt.locale("en_US"), "dd/MM/yyyy hh:mm:ss")
    }
    
    app.api.members.save(app.settings.member_id, JSON.stringify(obj)).then(function(data){
    	    console.log(data)
    })

###**remove(id, query)**
Posts a DELETE request to `resource` to delete an existing resource. `id` is the id of the resource to deleted, `query` is a comma separated list of key-value pairs, query is optional.

    app.api.favorites.remove(fav_id).then(function(){
        app.done()
    })


#SimplePromise holds callbacks to be executed by ResourceApi after receiving a response from the server

 

        app.api.images.get_one(image_id).then(function(data){
         console.log("successful response")
	    }, function(){
		    console.log("error response")
	    }, function(){
		    console.log("network error")
	    })
        
##Functions
 
###**then**(successCallback, serverErrorCallback, networkErrorCallback)

This function receives three functions to be executed by ResourceApi after receiving a response
    
`successCallback` will be executed when `ResourceApi` receives a success response from the server. `serverErrorCallback` will be executed when `ResourceApi` receives an error response from the server. `networkErrorCallback` will be executed if `ResourceApi` encounters a network error and couldn't reach remote server.
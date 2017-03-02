#Uploader uploads files using `app.restConsumer2`


    Uploader {
    	id: uploader
    }
    
    var images: []
    
    images.push("file1.png")
    images.push("file2.png")
    images.push("file3.png")
    images.push("file4.png")
    
    uploader.upload("/images/" + images)

##Functions

###**upload**(url, files)
This function uploads one or more file using `app.restConsumer2`. `url` is the url to upload files to, `url` will be appended to `app.restConsumer2`'s root url. `files` is an array of files to be uploaded.

##Signals

###**finished** (var total)
This signal will be emitted after all files are uploaded. `total` is the count of total files uploaded

###**serverError**(var err)
This signal will be emitted if `app.restConsumer2` receive an error response from the server

###**networkError**(var err)
This signal will be emitted if `app.restConsumer2` couldn't reach remote server

###**error**(var err)
This signal will be emitted by `app.restConsumer2` if an error occurs before uploading files

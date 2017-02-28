AnaPage is an essential part of Gurra


#**Properties**

   - **edit**: bool
	   a convenient property, should be true when editing a resourse

   - **loading**: bool
	    if true AnaPage will display a busy indicator to inform the user that something is going on
	    
   - **fetching**: bool
    	    if true AnaPage will display a busy indicator at the bottom of the page to inform the user that data is being fetched
    	    
   - **noInternet**: bool
    	    if true AnaPage will display an icon along with a text and button to all the user to try again 
    	    
   - **noContent**: bool
        	    if true AnaPage will display an icon along with a text and button to all the user to try again 
        	    
   - **noNetwork**: bool
        	    if true AnaPage will display an icon along with a text and button to all the user to try again 

   - **noInternet_button**: bool     
    `default: true`
	If true a TRY AGAIN button will be displayed if `noInternet` is true
		   
   - **noContent_button**: bool     
	   `default: true`
		   If true a TRY AGAIN button will be displayed if `noContent` is true
		   
   - **noNetwork_button**: bool     
	   `default: true`
		   If true a TRY AGAIN button will be displayed if `noNetwork` is true
		   
    **loading_message**: string
		    A text message to be displayed if `loading` is true
		    
    **noInternet_message**: string 
	    `default: No Connection`
    		    A text message to be displayed if `noInternet` is true
		    
    **noContent_message**: string 
	    `default: Sorry, no results that matchs your cretiera`
    		    A text message to be displayed if `noContent` is true
		    
    **noNetwork_message**: string 
    `default: Network connection error`
    		    A text message to be displayed if `noNetwork` is true
		    

    **noInternet_icon**: string  
    `default: app.icons.fontAwesome.exclamation`
        		    An icon be displayed if `noInternet` is true
		    
    **noContent_icon**:  string 
    `default: app.icons.fontAwesome.exclamation`
        		    An icon to be displayed if `noContent` is true
		    
    **noNetwork_icon**:  string
    `default: app.icons.fontAwesome.exclamation`
        		    An icon to be displayed if `noNetwork` is true
		    

#**Signals**

   **retry**
	   Will be emited when the user click `noContent_button` button 
	
   **retryConnection**
   	   Will be emited when the user click `noInternet_button` button 
	
   **retryNetwork**
	   Will be emited when the user click `noNetwork_message` button 
	
  **active**
  	   Will be emited when AnaPage is pushed on or poped of StackView. In many situation `enter` signal is preferred over `active`

  **activating**
    	   Will be emited when AnaPage is bieng pushed on or poped of StackView. In many situation `beforeEnter` signal is preferred over `activating`
    	   
  **inactive**
    	   Will be emited when AnaPage is poped of StackView. In many situation `leave` signal is preferred over `inactive`
    	   
 **beforeEnter**
     	   Will be emited before AnaPage is pushed on StackView. 
     	   
 **enter**
      	   Will be emited after AnaPage is pushed on StackView. 

**beforeLeave**
     	   Will be emited before AnaPage is poped of StackView. 

**leave**
     	   Will be emited after AnaPage is poped of StackView. 

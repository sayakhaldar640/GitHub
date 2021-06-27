({
    doInit : function(component, event, helper) {
      	// create the action
        let action = component.get("c.getItems");  
      	// add callback behaviour for when response is recieved
        action.setCallback(this, function(response){
            let state = response.getState();
            if(state === 'SUCCESS'){
                component.set("v.items", response.getReturnValue());
            }
            else{
                console.log("Failed with state: "+ state);
            }
        });
        // send action off to be executed
        $A.enqueueAction(action);
    },
    
    handleAddItem : function(component, event, helper) {
        var newItem = event.getParam("item");
        var action = component.get("c.saveItem");
        action.setParams({
            "campingItem" : newItem
        });
        action.setCallback(this, function(response){
            var state = response.getState();
            if(component.isValid() && state === "SUCCESS"){
                let items = component.get("v.items");
                items.push(newItem);
                component.set("v.items",items);
            }
        });
        $A.enqueueAction(action);   
    }
})
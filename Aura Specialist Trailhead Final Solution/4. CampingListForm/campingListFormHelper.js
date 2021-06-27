({
	createItem : function(component, campingItem) {
		/*let action = component.get("c.saveItem");
        action.setParam({
            "campingItem" : campingItem
        });
        action.setCallback(this, function(response){
            let state = response.getState();
            if(state === "SUCCESS"){
                let items = component.get("v.items");
                items.push(response.getReturnValue());
                component.set("v.items",items);
            } else {
                console.log("Failed with state: "+ state);
            }
        });
        $A.enqueueAction(action); */
        
        let createEvent = component.getEvent("addItem");
        createEvent.setParams({
            "item" : campingItem
        });
        createEvent.fire();
        
        component.set("v.newItem",
                            {'sobjectType':	'Camping_Item__c',
                            'Name':'',
                            'Quantity__c':0,
                            'Price__c':0,
                            'Packed__c':false});
	}
})
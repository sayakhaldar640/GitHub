({
	clickCreateItem : function(component, event, helper) {
		// Check for validation
        var checkField = component.find("itemform").reduce(function(validSoFar,inputCmp){
            // Display error messages for invalid fields
            inputCmp.showHelpMessageIfInvalid();
            return validSoFar && inputCmp.get("v.validity").valid;
        },true);
    
        if(checkField){
            // gets reference to view's newItem attribute
            /*var newItemRef = component.get("v.newItem");
            //console.log('Create Camping Item: '+ JSON.stringify(newItemRef));
        
            var theItems = JSON.parse(JSON.stringify(newItemRef));
            //theItems.push(newItem);
            //component.set("v.items",theItems);
            helper.createItem(component,theItems);
            component.set("v.newItem",
                            {'sobjectType':	'Camping_Item__c',
                            'Name':'',
                            'Quantity__c':0,
                            'Price__c':0,
                            'Packed__c':false}); */
            
           let addItem = event.getParam("v.newItem");
           helper.createItem(component, addItem);
        }
    }
})
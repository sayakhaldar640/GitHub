({
	packItem : function(component, event, helper) {
		//let buttonComp = event.getSource();
        component.set("v.item.Packed__c", true);
        component.set("v.Packed!",disabled="true");
	}
})
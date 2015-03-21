//
//  iOSHelper.cpp
//  canyon-flight
//
//  Created by Santhos Baala RS on 21/03/15.
//
//

#include "iOSHelper.h"
#include "AppController.h"

void iOSHelper::hideAdmobBanner(){
    AppController *appDelegate = (AppController *)[[UIApplication sharedApplication] delegate];
    [appDelegate hideAdmobBanner];
}

void iOSHelper::showAdmobBanner(){
    AppController *appDelegate = (AppController *)[[UIApplication sharedApplication] delegate];
    [appDelegate showAdmobBanner];
}
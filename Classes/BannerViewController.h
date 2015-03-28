//
//  BannerViewController.h
//  canyon-flight
//
//  Created by Santhos Baala RS on 21/03/15.
//
//

#ifndef canyon_flight_BannerViewController_h
#define canyon_flight_BannerViewController_h

#import <UIKit/UIKit.h>

@interface BannerViewController : UIViewController

- (instancetype)initWithContentViewController:(UIViewController *)contentController;
- (void) hideBanner;
- (void) showBanner;

@end

#endif

#import "BannerViewController.h"
#import <GoogleMobileAds/GoogleMobileAds.h>

@interface BannerViewController()<GADBannerViewDelegate>

@end

@implementation BannerViewController {
    GADBannerView *_bannerView;
    UIViewController *_contentController;
    Boolean _bannerLoaded;
}

- (instancetype)initWithContentViewController:(UIViewController *)contentController
{
    self = [super init];
    if (self != nil) {
        _bannerView = [[GADBannerView alloc] initWithAdSize: kGADAdSizeSmartBannerLandscape];
        _bannerView.adUnitID = @"ca-app-pub-8377744534015579/4275288840"; //REPLACE WITH YOUR OWN PUBLISHER ID
        _bannerView.delegate = self;
        _contentController = contentController;
        _bannerLoaded = NO;
    }
    return self;
}

- (void)loadView
{
    UIView *contentView = [[UIView alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    [self addChildViewController:_contentController];
    [contentView addSubview:_contentController.view];
    [_contentController didMoveToParentViewController:self];
    [contentView addSubview:_bannerView];
    self.view = contentView;
}

#if __IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_6_0
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return [_contentController shouldAutorotateToInterfaceOrientation:interfaceOrientation];
}
#endif

- (UIInterfaceOrientation)preferredInterfaceOrientationForPresentation
{
    return [_contentController preferredInterfaceOrientationForPresentation];
}

- (NSUInteger)supportedInterfaceOrientations
{
    return [_contentController supportedInterfaceOrientations];
}

// For animation
- (void)viewDidLayoutSubviews
{
    CGRect contentFrame = self.view.bounds;
    CGRect bannerFrame = CGRectZero;
#if __IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_6_0
    bannerFrame = _bannerView.frame;
#else
    bannerFrame.size = [_bannerView sizeThatFits:contentFrame.size];
#endif
    
    bannerFrame.origin.x = (contentFrame.size.width - bannerFrame.size.width) / 2;
    
    if (_bannerLoaded) {
        //contentFrame.size.height -= bannerFrame.size.height;
        bannerFrame.origin.y = contentFrame.size.height - bannerFrame.size.height;
    } else {
        bannerFrame.origin.y = contentFrame.size.height;
    }
    
    _contentController.view.frame = contentFrame;
    _bannerView.frame = bannerFrame;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    _bannerView.rootViewController = self;
    [self.view addSubview:_bannerView];
    
    GADRequest *request = [GADRequest request];
    [_bannerView loadRequest:request];
}

- (void)adViewDidReceiveAd:(GADBannerView *)bannerView
{
    _bannerLoaded = YES;
    [UIView animateWithDuration:0.25 animations:^{
        [self.view setNeedsLayout];
        [self.view layoutIfNeeded];
    }];
}

- (void)adView:(GADBannerView *)view didFailToReceiveAdWithError:(GADRequestError *)error
{
    _bannerLoaded = NO;
    [UIView animateWithDuration:0.25 animations:^{
        [self.view setNeedsLayout];
        [self.view layoutIfNeeded];
    }];
}

- (void) hideBanner{
    [_bannerView removeFromSuperview];
}

- (void) showBanner{
    [self.view addSubview:_bannerView];
    
    GADRequest *request = [GADRequest request];
    [_bannerView loadRequest:request];
}

- (void)dealloc {
    _bannerView.delegate = nil;
    [_bannerView release];
    [super dealloc];
}

@end
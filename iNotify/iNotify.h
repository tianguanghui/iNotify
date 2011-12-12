//
//  iNotify.h
//
//  Version 1.4
//
//  Created by Nick Lockwood on 26/01/2011.
//  Copyright 2011 Charcoal Design. All rights reserved.
//
//  http://charcoaldesign.co.uk/source/cocoa#inotify
//  https://github.com/nicklockwood/iNotify
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the authors be held liable for any damages
//  arising from the use of this software.
//
//  Permission is granted to anyone to use this software for any purpose,
//  including commercial applications, and to alter it and redistribute it
//  freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//  claim that you wrote the original software. If you use this software
//  in a product, an acknowledgment in the product documentation would be
//  appreciated but is not required.
//
//  2. Altered source versions must be plainly marked as such, and must not be
//  misrepresented as being the original software.
//
//  3. This notice may not be removed or altered from any source distribution.
//

#import <Foundation/Foundation.h>


static NSString *const iNotifyTitleKey = @"Title";
static NSString *const iNotifyMessageKey = @"Message";
static NSString *const iNotifyActionURLKey = @"ActionURL";
static NSString *const iNotifyActionButtonKey = @"ActionButton";
static NSString *const iNotifyMessageMinVersionKey = @"MinVersion";
static NSString *const iNotifyMessageMaxVersionKey = @"MaxVersion";


@protocol iNotifyDelegate <NSObject>
@optional

- (BOOL)iNotifyShouldCheckForNotifications;
- (void)iNotifyDidNotDetectNotifications;
- (void)iNotifyNotificationsCheckDidFailWithError:(NSError *)error;
- (void)iNotifyDidDetectNotifications:(NSDictionary *)notifications;
- (BOOL)iNotifyShouldDisplayNotificationWithKey:(NSString *)key details:(NSDictionary *)details;
- (void)iNotifyUserDidViewActionURLForNotificationWithKey:(NSString *)key details:(NSDictionary *)details;
- (void)iNotifyUserDidRequestReminderForNotificationWithKey:(NSString *)key details:(NSDictionary *)details;
- (void)iNotifyUserDidIgnoreNotificationWithKey:(NSString *)key details:(NSDictionary *)details;

@end


@interface iNotify : NSObject
#ifdef __i386__
{
	NSDictionary *notificationsDict;
	NSError *downloadError;
	NSString *notificationsPlistURL;
	BOOL showOldestFirst;
	BOOL showOnFirstLaunch;
	float checkPeriod;
	float remindPeriod;
	NSString *okButtonLabel;
	NSString *ignoreButtonLabel;
	NSString *remindButtonLabel;
	NSString *defaultActionButtonLabel;
	BOOL checkAtLaunch;
	BOOL debug;
	id<iNotifyDelegate> delegate;
}
#endif

+ (iNotify *)sharedInstance;

//notifications url - always set this
@property (nonatomic, copy) NSString *notificationsPlistURL;

//frequency settings - these have sensible defaults
@property (nonatomic, assign) BOOL showOldestFirst;
@property (nonatomic, assign) BOOL showOnFirstLaunch;
@property (nonatomic, assign) float checkPeriod;
@property (nonatomic, assign) float remindPeriod;

//message text, you may wish to customise these, e.g. for localisation
@property (nonatomic, copy) NSString *okButtonLabel;
@property (nonatomic, copy) NSString *ignoreButtonLabel;
@property (nonatomic, copy) NSString *remindButtonLabel;
@property (nonatomic, copy) NSString *defaultActionButtonLabel;

//debugging and automatic checks
@property (nonatomic, assign) BOOL checkAtLaunch;
@property (nonatomic, assign) BOOL debug;

//advanced properties for implementing custom behaviour
@property (nonatomic, copy) NSArray *ignoredNotifications;
@property (nonatomic, copy) NSArray *viewedNotifications;
@property (nonatomic, retain) NSDate *lastChecked;
@property (nonatomic, retain) NSDate *lastReminded;
@property (nonatomic, assign) id<iNotifyDelegate> delegate;

//manually control behaviour
- (NSString *)nextNotificationInDict:(NSDictionary *)dict;
- (void)setNotificationIgnored:(NSString *)key;
- (void)setNotificationViewed:(NSString *)key;
- (BOOL)shouldCheckForNotifications;
- (void)checkForNotifications;

@end

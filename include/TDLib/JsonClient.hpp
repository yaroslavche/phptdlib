#ifndef TDLIB_JSONCLIENT_H
#define TDLIB_JSONCLIENT_H

#include <nlohmann/json.hpp>
#include "BaseJsonClient.hpp"

class JsonClient : public BaseJsonClient
{
    private:
        std::string lastResponse;
        std::vector<std::string> receivedResponses;
        std::vector<nlohmann::json> receivedResponsesExtras;
        std::string authorizationState;
        std::string connectionState;
        double defaultTimeout = 0.5;

        void handleResponses(nlohmann::json* breakOnExtra);
        std::string waitForResponse(nlohmann::json* extra,double timeout);

        std::string query(const char *query, double timeout, nlohmann::json* extra);
        std::string addExtraAndSendQuery(std::string type, nlohmann::json* jsonQuery, double timeout);
        double getTimeoutFromParams(Php::Parameters &params, int timeoutParameterInde);

    public:

        // exported
        // BaseJsonClient
        inline void __construct(Php::Parameters &params) { BaseJsonClient::__construct(params);};
        inline void __destruct() { BaseJsonClient::__destruct();};
        inline void create() { BaseJsonClient::create(); }
        inline void destroy() { BaseJsonClient::destroy(); }
        inline Php::Value execute(Php::Parameters &params) { return BaseJsonClient::execute(params); }
        inline void send(Php::Parameters &params) { BaseJsonClient::send(params); }
        Php::Value receive(Php::Parameters &params);

        // JsonClient
        Php::Value query(Php::Parameters &params);
        Php::Value getReceivedResponses(Php::Parameters &params);
        void setDefaultTimeout(Php::Parameters &params);

        // tdlib Function Class Reference
        Php::Value checkDatabaseEncryptionKey(Php::Parameters &params);
        Php::Value getAuthorizationState(Php::Parameters &params);
        Php::Value setAuthenticationPhoneNumber(Php::Parameters &params);
        Php::Value setDatabaseEncryptionKey(Php::Parameters &params);
        Php::Value setTdlibParameters(Php::Parameters &params);
};

#endif // TDLIB_JSONCLIENT_H

// https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1_function.html
/*
- [ ] acceptCall
- [ ] acceptTermsOfService
- [ ] addChatMember
- [ ] addChatMembers
- [ ] addFavoriteSticker
- [ ] addLocalMessage
- [ ] addNetworkStatistics
- [ ] addProxy
- [ ] addRecentlyFoundChat
- [ ] addRecentSticker
- [ ] addSavedAnimation
- [ ] addStickerToSet
- [ ] answerCallbackQuery
- [ ] answerCustomQuery
- [ ] answerInlineQuery
- [ ] answerPreCheckoutQuery
- [ ] answerShippingQuery
- [ ] blockUser
- [ ] cancelDownloadFile
- [ ] cancelUploadFile
- [ ] changeChatReportSpamState
- [ ] changeImportedContacts
- [ ] changePhoneNumber
- [ ] changeStickerSet
- [ ] checkAuthenticationBotToken
- [ ] checkAuthenticationCode
- [ ] checkAuthenticationPassword
- [ ] checkChangePhoneNumberCode
- [ ] checkChatInviteLink
- [ ] checkChatUsername
- [X] checkDatabaseEncryptionKey
- [ ] checkEmailAddressVerificationCode
- [ ] checkPhoneNumberConfirmationCode
- [ ] checkPhoneNumberVerificationCode
- [ ] cleanFileName
- [ ] clearAllDraftMessages
- [ ] clearImportedContacts
- [ ] clearRecentlyFoundChats
- [ ] clearRecentStickers
- [ ] close
- [ ] closeChat
- [ ] closeSecretChat
- [ ] createBasicGroupChat
- [ ] createCall
- [ ] createNewBasicGroupChat
- [ ] createNewSecretChat
- [ ] createNewStickerSet
- [ ] createNewSupergroupChat
- [ ] createPrivateChat
- [ ] createSecretChat
- [ ] createSupergroupChat
- [ ] createTemporaryPassword
- [ ] deleteAccount
- [ ] deleteChatHistory
- [ ] deleteChatMessagesFromUser
- [ ] deleteChatReplyMarkup
- [ ] deleteFile
- [ ] deleteLanguagePack
- [ ] deleteMessages
- [ ] deletePassportElement
- [ ] deleteProfilePhoto
- [ ] deleteSavedCredentials
- [ ] deleteSavedOrderInfo
- [ ] deleteSupergroup
- [ ] destroy
- [ ] disableProxy
- [ ] discardCall
- [ ] disconnectAllWebsites
- [ ] disconnectWebsite
- [ ] downloadFile
- [ ] editCustomLanguagePackInfo
- [ ] editInlineMessageCaption
- [ ] editInlineMessageLiveLocation
- [ ] editInlineMessageMedia
- [ ] editInlineMessageReplyMarkup
- [ ] editInlineMessageText
- [ ] editMessageCaption
- [ ] editMessageLiveLocation
- [ ] editMessageMedia
- [ ] editMessageReplyMarkup
- [ ] editMessageText
- [ ] editProxy
- [ ] enableProxy
- [ ] finishFileGeneration
- [ ] forwardMessages
- [ ] generateChatInviteLink
- [ ] getAccountTtl
- [ ] getActiveLiveLocationMessages
- [ ] getActiveSessions
- [ ] getAllPassportElements
- [ ] getArchivedStickerSets
- [ ] getAttachedStickerSets
- [X] getAuthorizationState
- [ ] getBasicGroup
- [ ] getBasicGroupFullInfo
- [ ] getBlockedUsers
- [ ] getCallbackQueryAnswer
- [ ] getChat
- [ ] getChatAdministrators
- [ ] getChatEventLog
- [ ] getChatHistory
- [ ] getChatMember
- [ ] getChatMessageByDate
- [ ] getChatMessageCount
- [ ] getChatPinnedMessage
- [ ] getChatReportSpamState
- [ ] getChats
- [ ] getConnectedWebsites
- [ ] getContacts
- [ ] getCountryCode
- [ ] getCreatedPublicChats
- [ ] getDeepLinkInfo
- [ ] getFavoriteStickers
- [ ] getFile
- [ ] getFileExtension
- [ ] getFileMimeType
- [ ] getGameHighScores
- [ ] getGroupsInCommon
- [ ] getImportedContactCount
- [ ] getInlineGameHighScores
- [ ] getInlineQueryResults
- [ ] getInstalledStickerSets
- [ ] getInviteText
- [ ] getLanguagePackString
- [ ] getLanguagePackStrings
- [ ] getLocalizationTargetInfo
- [ ] getMapThumbnailFile
- [ ] getMe
- [ ] getMessage
- [ ] getMessages
- [ ] getNetworkStatistics
- [ ] getOption
- [ ] getPassportAuthorizationForm
- [ ] getPassportElement
- [ ] getPasswordState
- [ ] getPaymentForm
- [ ] getPaymentReceipt
- [ ] getPreferredCountryLanguage
- [ ] getProxies
- [ ] getProxyLink
- [ ] getPublicMessageLink
- [ ] getRecentInlineBots
- [ ] getRecentlyVisitedTMeUrls
- [ ] getRecentStickers
- [ ] getRecoveryEmailAddress
- [ ] getRemoteFile
- [ ] getRepliedMessage
- [ ] getSavedAnimations
- [ ] getSavedOrderInfo
- [ ] getScopeNotificationSettings
- [ ] getSecretChat
- [ ] getStickerEmojis
- [ ] getStickers
- [ ] getStickerSet
- [ ] getStorageStatistics
- [ ] getStorageStatisticsFast
- [ ] getSupergroup
- [ ] getSupergroupFullInfo
- [ ] getSupergroupMembers
- [ ] getSupportUser
- [ ] getTemporaryPasswordState
- [ ] getTextEntities
- [ ] getTopChats
- [ ] getTrendingStickerSets
- [ ] getUser
- [ ] getUserFullInfo
- [ ] getUserPrivacySettingRules
- [ ] getUserProfilePhotos
- [ ] getWallpapers
- [ ] getWebPageInstantView
- [ ] getWebPagePreview
- [ ] importContacts
- [ ] joinChat
- [ ] joinChatByInviteLink
- [ ] leaveChat
- [ ] logOut
- [ ] openChat
- [ ] openMessageContent
- [ ] optimizeStorage
- [ ] parseTextEntities
- [ ] pingProxy
- [ ] pinSupergroupMessage
- [ ] processDcUpdate
- [ ] readAllChatMentions
- [ ] recoverAuthenticationPassword
- [ ] recoverPassword
- [ ] registerDevice
- [ ] removeContacts
- [ ] removeFavoriteSticker
- [ ] removeProxy
- [ ] removeRecentHashtag
- [ ] removeRecentlyFoundChat
- [ ] removeRecentSticker
- [ ] removeSavedAnimation
- [ ] removeStickerFromSet
- [ ] removeTopChat
- [ ] reorderInstalledStickerSets
- [ ] reportChat
- [ ] reportSupergroupSpam
- [ ] requestAuthenticationPasswordRecovery
- [ ] requestPasswordRecovery
- [ ] resendAuthenticationCode
- [ ] resendChangePhoneNumberCode
- [ ] resendEmailAddressVerificationCode
- [ ] resendPhoneNumberConfirmationCode
- [ ] resendPhoneNumberVerificationCode
- [ ] resetAllNotificationSettings
- [ ] resetNetworkStatistics
- [ ] searchCallMessages
- [ ] searchChatMembers
- [ ] searchChatMessages
- [ ] searchChatRecentLocationMessages
- [ ] searchChats
- [ ] searchChatsOnServer
- [ ] searchContacts
- [ ] searchHashtags
- [ ] searchInstalledStickerSets
- [ ] searchMessages
- [ ] searchPublicChat
- [ ] searchPublicChats
- [ ] searchSecretMessages
- [ ] searchStickers
- [ ] searchStickerSet
- [ ] searchStickerSets
- [ ] sendBotStartMessage
- [ ] sendCallDebugInformation
- [ ] sendCallRating
- [ ] sendChatAction
- [ ] sendChatScreenshotTakenNotification
- [ ] sendChatSetTtlMessage
- [ ] sendCustomRequest
- [ ] sendEmailAddressVerificationCode
- [ ] sendInlineQueryResultMessage
- [ ] sendMessage
- [ ] sendMessageAlbum
- [ ] sendPassportAuthorizationForm
- [ ] sendPaymentForm
- [ ] sendPhoneNumberConfirmationCode
- [ ] sendPhoneNumberVerificationCode
- [ ] setAccountTtl
- [ ] setAlarm
- [X] setAuthenticationPhoneNumber
- [ ] setBio
- [ ] setBotUpdatesStatus
- [ ] setChatClientData
- [ ] setChatDraftMessage
- [ ] setChatMemberStatus
- [ ] setChatNotificationSettings
- [ ] setChatPhoto
- [ ] setChatTitle
- [ ] setCustomLanguagePack
- [ ] setCustomLanguagePackString
- [X] setDatabaseEncryptionKey
- [ ] setFileGenerationProgress
- [ ] setGameScore
- [ ] setInlineGameScore
- [ ] setName
- [ ] setNetworkType
- [ ] setOption
- [ ] setPassportElement
- [ ] setPassportElementErrors
- [ ] setPassword
- [ ] setPinnedChats
- [ ] setProfilePhoto
- [ ] setRecoveryEmailAddress
- [ ] setScopeNotificationSettings
- [ ] setStickerPositionInSet
- [ ] setSupergroupDescription
- [ ] setSupergroupStickerSet
- [ ] setSupergroupUsername
- [X] setTdlibParameters
- [ ] setUsername
- [ ] setUserPrivacySettingRules
- [ ] terminateAllOtherSessions
- [ ] terminateSession
- [ ] testCallBytes
- [ ] testCallEmpty
- [ ] testCallString
- [ ] testCallVectorInt
- [ ] testCallVectorIntObject
- [ ] testCallVectorString
- [ ] testCallVectorStringObject
- [ ] testGetDifference
- [ ] testNetwork
- [ ] testSquareInt
- [ ] testUseError
- [ ] testUseUpdate
- [ ] toggleBasicGroupAdministrators
- [ ] toggleChatDefaultDisableNotification
- [ ] toggleChatIsMarkedAsUnread
- [ ] toggleChatIsPinned
- [ ] toggleSupergroupInvites
- [ ] toggleSupergroupIsAllHistoryAvailable
- [ ] toggleSupergroupSignMessages
- [ ] unblockUser
- [ ] unpinSupergroupMessage
- [ ] upgradeBasicGroupChatToSupergroupChat
- [ ] uploadFile
- [ ] uploadStickerFile
- [ ] validateOrderInfo
- [ ] viewMessages
- [ ] viewTrendingStickerSets

*/

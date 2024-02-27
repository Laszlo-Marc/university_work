#include "TestValidation.h"
#include "Validation.h"
#include <string>
#include <assert.h>
#include <tuple>

void testValidation::testValidateDuration()
{
	Validator* testValidator = new Validator();
	string validDuration = "12:45:46";
	int hours=0, minutes=0, seconds=0;
	tie(hours, minutes, seconds) = testValidator->validateDuration(validDuration);
	assert(hours == 12);
	assert(minutes == 45);
	assert(seconds == 46);
	string invalidDuration = "12:67:100";
	int hours2, minutes2, seconds2;
	tie(hours2, minutes2, seconds2) = testValidator->validateDuration(invalidDuration);
	assert(hours2 == -1);
	assert(minutes2 == -1);
	assert(seconds2 == -1);
	string invalidDuration2 = "12:-1:-2";
	int hours3, minutes3, seconds3;
	tie(hours3, minutes3, seconds3) = testValidator->validateDuration(invalidDuration2);
	assert(hours3 == -1);
	assert(minutes3 == -1);
	assert(seconds3 == -1);
	string invalidDuration3 = "aa:bb:cc";
	int hours4, minutes4, seconds4;
	tie(hours4, minutes4, seconds4) = testValidator->validateDuration(invalidDuration3);
	assert(hours4 == -1);
	assert(minutes4 == -1);
	assert(seconds4 == -1);
	delete testValidator;

}

void testValidation::testValidateLikes()
{
	Validator* testValidator = new Validator();
	string validLikes = "123000";
	assert(testValidator->validateLikes(validLikes) == 123000);
	string invalidLikes = "abvajfa";
	assert(testValidator->validateLikes(invalidLikes) == -1);
	delete testValidator;
}

void testValidation::testValidateLink()
{
	Validator* testValidator = new Validator();
	string validLink = "https://www.youtube.com/watch?v=vLnPwxZdW4Y";
	assert(testValidator->validateLink(validLink));
	string invalidLink = "hwatch?v=vLnPwxZdW4Y";
	assert(!testValidator->validateLink(invalidLink));
	delete testValidator;
}

void testValidation::testAllValidate()
{
	testValidateDuration();
	testValidateLikes();
	testValidateLink();
}

/*
### 아래 세줄 키 입력하여 properties에 등록
azure.activedirectory.tenant-id=
azure.activedirectory.client-id=
azure.activedirectory.client-secret=
*/

@Override
protected void configure(HttpSecurity http) throws Exception {
    http.cors()
            .and()
            .csrf().disable()
            .exceptionHandling().authenticationEntryPoint(unauthorizedHandler)
            .and()
            .sessionManagement().sessionCreationPolicy(SessionCreationPolicy.STATELESS)
            .and()
            .authorizeRequests()
            .antMatchers(AUTH_WHITELIST).permitAll()
            .anyRequest().authenticated()
            .and()
            .oauth2Login().authorizationEndpoint().authorizationRequestResolver(aadRequestResolver())
            .and()
            .tokenEndpoint()
            .accessTokenResponseClient(aadAccessTokenResponseClient())
            .and()
            .userInfoEndpoint()
            .oidcUserService(aadOAuth2UserService())
            .and()
            .successHandler(ssoAuthenticationSuccessHandler)
            .failureHandler(ssoAuthenticationFailureHandler)
    ;

    http.addFilterBefore(authenticationJwtTokenFilter(), UsernamePasswordAuthenticationFilter.class);
}

protected OAuth2AuthorizationRequestResolver aadRequestResolver() {
    return new AADOAuth2AuthorizationRequestResolver(this.repo, properties);
}


protected OAuth2AccessTokenResponseClient<OAuth2AuthorizationCodeGrantRequest> aadAccessTokenResponseClient() {
    DefaultAuthorizationCodeTokenResponseClient result = new DefaultAuthorizationCodeTokenResponseClient();
    if (repo instanceof AADClientRegistrationRepository) {
        result.setRequestEntityConverter(
                new AADOAuth2AuthorizationCodeGrantRequestEntityConverter(
                        ((AADClientRegistrationRepository) repo).getAzureClientAccessTokenScopes()));
    }
    return result;
}


public AADOAuth2UserService aadOAuth2UserService() {
    return new AADOAuth2UserService(properties);
}


@Slf4j
@Component
public class AuthenticationSuccessHandler extends SimpleUrlAuthenticationSuccessHandler {

    @Value("${oauth.azure.successUrl}")
    private String successReUrl;

    @Override
    public void onAuthenticationSuccess(HttpServletRequest request, HttpServletResponse response, Authentication authentication) throws IOException, ServletException {
        setDefaultTargetUrl(successReUrl);
        SecurityContextHolder.getContext().setAuthentication(null);
        OAuth2User oAuth2User = (OAuth2User) authentication.getPrincipal();

        // 여기 로직 작성

        super.onAuthenticationSuccess(request, response, authentication);
    }
}

@Component
@Slf4j
public class AuthenticationFailureHandler extends SimpleUrlAuthenticationFailureHandler {

    @Value("${oauth.azure.failureUrl}")
    private String failureReUrl;

    @Override
    public void onAuthenticationFailure(HttpServletRequest request, HttpServletResponse response, AuthenticationException exception) throws IOException, ServletException {
        setDefaultFailureUrl(failureReUrl);

        super.onAuthenticationFailure(request, response, exception);
    }
}